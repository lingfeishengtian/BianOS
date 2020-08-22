#include <stdint.h>

typedef struct page
{
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t user       : 1;
    uint32_t accessed   : 1;
    uint32_t dirty      : 1;
    uint32_t unused     : 7;
    uint32_t frame      : 20;
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t * page_tables[1024];
    uint32_t page_table_physical[1024];
    uint32_t physical_addr;
} page_directory_t;

extern void kernel_physical_start(void);
void* kernel_phys_placement = &kernel_physical_start;

