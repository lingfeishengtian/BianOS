#include "kheap.h"
#include "paging/paging.h"
#include <stdbool.h>

void kernel_virtual_start(void);
void kernel_virtual_end(void);
void kernel_physical_end(void);

void* kernel_placement_addr = &kernel_virtual_end;
void* phys_placement_addr = 0;

#define ALIGN_CMP_ADDRESS 0x00000FFF
#define ALIGN_ADDRESS 0xFFFFF000

//TODO: Implement kfree()

void* kmalloc_internal(uint32_t size, uint8_t align, void** placement_addr_pt){
    void* placement_addr = *placement_addr_pt;
    uint32_t integral_addr = (uint32_t) placement_addr;
    if((align & 0x1) && (integral_addr & ALIGN_CMP_ADDRESS)){
        placement_addr = (void*) (integral_addr & ALIGN_ADDRESS);
        placement_addr += PAGE_SIZE;
    }
    
    void* tmp = placement_addr;
    placement_addr += size;

    *placement_addr_pt = placement_addr;

    if(paging_initialized){
        uint32_t tmp_ret = (uint32_t) tmp;
        while(tmp_ret <= (uint32_t) placement_addr){
            alloca_page_addr((uint32_t) tmp_ret);
            tmp_ret += PAGE_SIZE;
        }
    }

    return tmp;
}

void* kmalloc_a(uint32_t size){
    return kmalloc_internal(size, 1, &kernel_placement_addr);
}

void* kmalloc(uint32_t size){
    return kmalloc_internal(size, 0, &kernel_placement_addr);
}

void* malloc(uint32_t size){
    return kmalloc_internal(size, 0, &phys_placement_addr);
}