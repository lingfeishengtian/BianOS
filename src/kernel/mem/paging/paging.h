#include <stdbool.h>
#include <stdint.h>
#include "../kheap.h"

extern bool paging_initialized;

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
    page_t pages[PAGE_TABLE_COUNT];
} page_table_t;

typedef struct page_directory
{
    page_table_t * page_tables[PAGE_TABLE_COUNT];
    uint32_t page_table_physical[PAGE_TABLE_COUNT];
} page_directory_t;

void alloca_page_addr(uint32_t addr);
void init_paging();