#include <stdint.h>

extern void* placement_addr;

void* kmalloc_a(uint32_t size);
void* kmalloc(uint32_t size);