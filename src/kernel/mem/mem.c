#include "mem.h"

void kernel_virtual_start(void);
void kernel_virtual_end(void);

void* placement_addr = &kernel_virtual_end;

void* kmalloc_internal(unsigned int size, unsigned char align, unsigned int *phys){
    unsigned int integral_addr = (unsigned int) placement_addr;
    if((align & 0x1) && (integral_addr & 0x00000FFF)){
        placement_addr = (void*) (integral_addr & 0xFFFFF000);
        placement_addr += 0x00001000;
    }
    
    if(phys){
        *phys = (unsigned int) placement_addr;
    }
    
    void* tmp = placement_addr;
    placement_addr += size;
    return tmp;
}

void* kmalloc_a(unsigned int size){
    return kmalloc_internal(size, 1, 0);
}

void* kmalloc(unsigned int size){
    return kmalloc_internal(size, 0, 0);
}