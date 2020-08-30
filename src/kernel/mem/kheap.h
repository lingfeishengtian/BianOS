#include <stdint.h>

extern void* kernel_placement_addr;

void* kmalloc_a(uint32_t size);
void* kmalloc(uint32_t size);

void* malloc(uint32_t size);