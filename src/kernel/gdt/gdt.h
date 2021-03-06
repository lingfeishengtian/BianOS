#include <stdint.h>

#define GDT_SIZE 5
#define GDT_GRANULARITY 0xCF
#define GDT_SUPER_CODE_ACCESS 0x9A
#define GDT_SUPER_DATA_ACCESS 0x92
#define GDT_USER_CODE_ACCESS (GDT_SUPER_CODE_ACCESS | 0x40)
#define GDT_USER_DATA_ACCESS (GDT_SUPER_DATA_ACCESS | 0x40)

/** gdt:
 * Size:
 * short -> 2 bytes
 * The total size of the table minus 1.
 * 
 * Offset:
 * int -> 4 bytes (using 32 bit)
 * The location of the gdt table.
 */
struct gdt {
    uint16_t size;
    uint32_t offset;
} __attribute__ ((packed));

/** gdt_entry:
 * GDT requires 8 byte gdt_entries, so __attribute__ ((packed)) is required as it packs our struct so the compiler doesn't optimize it.
 * View https://wiki.osdev.org/images/f/f3/GDT_Entry.png for a graph of this.
 * 
 * 0 - 15: limit_low
 * short -> 16 bits/2 bytes
 * The first 16 bits of the 20 bit limit address (max address this entry can reach).
 * 1 byte units or in pages.
 * 
 * 16 - 31: base_low
 * short -> 16 bits/2 bytes
 * The first 16 bits of the 32 bit base address (where the segment begins).
 * Linear address.
 * 
 * 32 - 39: base_middle
 * char -> 8 bits/1 byte
 * 8 bits after 16 completed entered bits of the 32 bit base address (24/32 complete)
 * 
 * 40 - 47: access
 * char -> 8 bits/1 byte
 * Many different configurations for the access byte. (found here https://wiki.osdev.org/Global_Descriptor_Table)
 * 
 * 48 - 55: limit_high_and_flags
 * char -> 8 bits/1 byte
 * This one's a doozy. In the granularity byte, the first 4 bits are the 4 most significant bits of the limit address.
 * The 4 most significant bits of this byte are the flags and are defined as | Granularity bit | Size bit (16 bit or 32 bit mode) | 0 | 0 |
 * 
 * 56 - 63: base_high
 * char -> 8 bits/1 byte
 * Highest 8 bits of the linear base address of the segment.
 */
struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
} __attribute__ ((packed));

/** setup_gdt:
 * Creates our gdt table with code segment registers and data segment registers.
 */
void setup_gdt();