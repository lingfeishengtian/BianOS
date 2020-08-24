#include "paging.h"
#include "../kheap.h"
#include "../mem.h"
#include "../../error/error_handler.h"
#include "../../../drivers/vga_text.h"
#include "../../debugger.h"

uint32_t *frames;
uint32_t nframes;

#define INDEX_OF_FRAME(x) x / 32
#define OFFSET_OF_FRAME(x) x % 32

extern void switch_page_directory(uint32_t);

void set_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000;
    uint32_t ind = INDEX_OF_FRAME(frame);
    frames[ind] |= 0x1 << OFFSET_OF_FRAME(frame);
}

bool test_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000;
    uint32_t ind = INDEX_OF_FRAME(frame);
    return frames[ind] & 0x1 << OFFSET_OF_FRAME(frame);
}

void clear_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr / 0x1000;
    uint32_t ind = INDEX_OF_FRAME(frame);
    frames[ind] ^= 0x1 << OFFSET_OF_FRAME(frame);
}

uint32_t find_first_free_frame(){
    uint32_t i, j;
    for(i = 0; i < INDEX_OF_FRAME(nframes); ++i){
        if(frames[i] != 0xFFFFFFFF){
            for (j = 0; j < 32; ++j)
            {
                if(!(frames[i] & 0x1 << j)){
                    return i * 32 + j;
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
        
        if(free_frame * 0x1000 == sizeof(uint32_t) - 1){
            kprintf("[KERNEL PANIC] No free frames!", RED, BLACK);
            panic();
        }

        set_frame(free_frame * 0x1000);
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
        clear_frame(frame * 0x1000);
        page->frame = 0x0;
    }
}

const uint32_t virt_start = 0xC0000000;

page_t * create_page(uint32_t addr, page_directory_t * dir){
    addr /= 0x1000;
    uint32_t table_ind = addr / 1024;

    if(dir->page_tables[table_ind]){
        return &dir->page_tables[table_ind]->pages[addr % 1024];
    }else{
        page_table_t* virt = kmalloc_a(sizeof(page_table_t));
        memset(virt, 0, 0x1000);
        dir->page_table_physical[table_ind] = ((uint32_t) virt - virt_start) | 0x7;
        dir->page_tables[table_ind] = virt;
        return &dir->page_tables[table_ind]->pages[addr % 1024];
    }
}

page_directory_t * cur_dir;

void alloca_page_addr(uint32_t addr){
    alloca_frame(create_page(addr, cur_dir), true, true);
}

void init_paging(){
    //TODO: Actually check the memory size! Currently 128 MiB for QEMU size
    uint32_t mem_size = 0x8000000;
    nframes = mem_size / 0x1000;
    frames = (uint32_t *) kmalloc(INDEX_OF_FRAME(nframes));
    memset(frames, 0, INDEX_OF_FRAME(nframes));

    page_directory_t * pg_dir = kmalloc_a(sizeof(page_directory_t));
    memset(pg_dir, 0, sizeof(page_directory_t));
    cur_dir = pg_dir;

    kprint_str("Starting identity map of addresses all to final used memory value.\n");
    uint32_t i = 0;
    while (i < 0x00100000)
    {
        alloca_frame(create_page(i, pg_dir), true, true);
        i += 0x1000;
    }

    i = virt_start;
    while (i <= (uint32_t) placement_addr)
    {
        page_t* tmp = create_page(i, pg_dir);
        tmp->frame = (i - 0xC0000000) >> 12;
        tmp->present = 1;
        tmp->rw = 1;
        tmp->user = 1;
        i += 0x1000;
    }

    kprintf("Changing page directory.\nAddress of page directory: %x\n", MAGENTA, BLACK, cur_dir->page_table_physical);
    switch_page_directory((uint32_t) pg_dir->page_table_physical);
}