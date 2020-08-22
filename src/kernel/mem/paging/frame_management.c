#include "frame_management.h"
#include "../../error/error_handler.h"
#include "../../../drivers/vga_text.h"

uint32_t *frames;
uint32_t nframes;

#define INDEX_OF_FRAME(x) x / 32
#define OFFSET_OF_FRAME(x) x % 32

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
        
        if(free_frame < sizeof(uint32_t) - 1){
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
        clear_frame(frame);
        page->frame = 0x0;
    }
}