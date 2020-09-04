#include <stdint.h>

#define MEM_SIZE 0x8000000
#define PAGE_SIZE 0x1000
#define PAGE_CONFIG 0x7
#define VIRTUAL_START 0xC0000000
#define PAGE_TABLE_COUNT 1024

extern void* kernel_placement_addr;

void* kmalloc_a(uint32_t size);
void* kmalloc(uint32_t size);

void* malloc(uint32_t size);