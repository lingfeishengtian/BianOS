#include "kheap.h"

void kernel_virtual_start(void);
void kernel_virtual_end(void);

void* placement_addr = &kernel_virtual_end;

void* kmalloc_internal(uint32_t size, uint8_t align, uint32_t *phys){
    uint32_t integral_addr = (uint32_t) placement_addr;
    if((align & 0x1) && (integral_addr & 0x00000FFF)){
        placement_addr = (void*) (integral_addr & 0xFFFFF000);
        placement_addr += 0x00001000;
    }
    
    if(phys){
        *phys = (uint32_t) placement_addr;
    }
    
    void* tmp = placement_addr;
    placement_addr += size;
    return tmp;
}

void* kmalloc_a(uint32_t size){
    return kmalloc_internal(size, 1, 0);
}

void* kmalloc(uint32_t size){
    return kmalloc_internal(size, 0, 0);
}