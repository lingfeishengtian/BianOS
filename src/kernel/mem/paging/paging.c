#include "paging.h"
#include "../mem.h"
#include "../../error/error_handler.h"
#include "../../../drivers/vga_text.h"
#include "../../debugger.h"

uint32_t *frames;
uint32_t nframes;

#define BIT_SIZE 32
#define INDEX_OF_FRAME(x) x / BIT_SIZE
#define OFFSET_OF_FRAME(x) x % BIT_SIZE

extern void switch_page_directory(uint32_t);

void set_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / PAGE_SIZE;
    uint32_t ind = INDEX_OF_FRAME(frame);
    frames[ind] |= 0x1 << OFFSET_OF_FRAME(frame);
}

bool test_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / PAGE_SIZE;
    uint32_t ind = INDEX_OF_FRAME(frame);
    return frames[ind] & 0x1 << OFFSET_OF_FRAME(frame);
}

void clear_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / PAGE_SIZE;
    uint32_t ind = INDEX_OF_FRAME(frame);
    frames[ind] ^= 0x1 << OFFSET_OF_FRAME(frame);
}

uint32_t find_first_free_frame(){
    uint32_t i, j;
    for(i = 0; i < INDEX_OF_FRAME(nframes); ++i){
        if(frames[i] != 0xFFFFFFFF){
            for (j = 0; j < BIT_SIZE; ++j)
            {
                if(!(frames[i] & 0x1 << j)){
                    return i * BIT_SIZE + j;
                }
            }
            
        }
    }
    return 0;
}

uint32_t alloca_frame(page_t * page, bool is_kernel, bool is_writeable){
    if(page->frame != 0){
        return 0;
    }else{
        uint32_t free_frame = find_first_free_frame();
        
        if(free_frame * PAGE_SIZE == sizeof(uint32_t) - 1){
            kprintf("[KERNEL PANIC] No free frames!", RED, BLACK);
            panic();
        }

        set_frame(free_frame * PAGE_SIZE);
        page->frame = free_frame;
        page->present = 1;
        page->rw = is_writeable;
        page->user = !is_kernel;
        return free_frame;
    }
}

void free_frame(page_t * page)
{
    uint32_t frame = page->frame;
    if(!frame){
        return;
    }else{
        clear_frame(frame * PAGE_SIZE);
        page->frame = 0x0;
    }
}

page_t * create_page(uint32_t addr, page_directory_t * dir){
    addr /= PAGE_SIZE;
    uint32_t table_ind = addr / PAGE_TABLE_COUNT;

    if(dir->page_tables[table_ind]){
        return &dir->page_tables[table_ind]->pages[addr % PAGE_TABLE_COUNT];
    }else{
        page_table_t* virt = kmalloc_a(sizeof(page_table_t));
        memset(virt, 0, PAGE_SIZE);
        dir->page_table_physical[table_ind] = ((uint32_t) virt - VIRTUAL_START) | PAGE_CONFIG;
        dir->page_tables[table_ind] = virt;
        return &dir->page_tables[table_ind]->pages[addr % PAGE_TABLE_COUNT];
    }
}

bool paging_initialized = false;
page_directory_t * cur_dir;

void alloca_page_addr(uint32_t addr){
    alloca_frame(create_page(addr, cur_dir), true, true);
}

void init_paging(){
    //TODO: Actually check the memory size! Currently 128 MiB for QEMU size
    uint32_t mem_size = MEM_SIZE;
    nframes = mem_size / PAGE_SIZE;
    frames = (uint32_t *) kmalloc(INDEX_OF_FRAME(nframes));
    memset(frames, 0, INDEX_OF_FRAME(nframes));

    page_directory_t * pg_dir = kmalloc_a(sizeof(page_directory_t));
    memset(pg_dir, 0, sizeof(page_directory_t));
    cur_dir = pg_dir;

    kprint_str("Starting identity map of addresses all to final used memory value.\n");
    uint32_t i = 0;

    i = VIRTUAL_START;
    while (i <= (uint32_t) kernel_placement_addr)
    {
        page_t* tmp = create_page(i, pg_dir);
        tmp->frame = (i - VIRTUAL_START) >> 12;
        tmp->present = 1;
        tmp->rw = 1;
        tmp->user = 1;
        set_frame(i);
        i += PAGE_SIZE;
    }

    kprintf("Changing page directory.\nAddress of page directory: %x\n", MAGENTA, BLACK, cur_dir->page_table_physical);
    switch_page_directory((uint32_t) pg_dir->page_table_physical);
    paging_initialized = true;
    return;
}