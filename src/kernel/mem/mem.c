#include "mem.h"

void kernel_virtual_start(void);
void kernel_virtual_end(void);

unsigned int placement_addr = (unsigned int) &kernel_virtual_end;

unsigned int kmalloc_internal(unsigned int size, unsigned char align, unsigned int *phys){
    if((align & 0x1) && (placement_addr & 0x00000FFF)){
        placement_addr &= 0xFFFFF000;
        placement_addr += 0x00001000;
    }
    if(phys){
        *phys = placement_addr;
    }
    unsigned int tmp = placement_addr;
    placement_addr += size;
    return tmp;
}

unsigned int kmalloc_a(unsigned int size){
    return kmalloc_internal(size, 1, 0);
}

unsigned int kmalloc(unsigned int size){
    return kmalloc_internal(size, 0, 0);
}