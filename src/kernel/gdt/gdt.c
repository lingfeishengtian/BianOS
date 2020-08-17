#include "gdt.h"
#include "../debugger.h"

/** gdt_flush:
 * Flush our segment registers
 */
extern void gdt_flush(unsigned int);

// We define our GDT now.
struct gdt gdt_ptr;
struct gdt_entry gdt_entries[3];

/** internal create_gdt_entry
 * Creates a gdt entry at an index.
 * 
 * @param index The index for the gdt_entry to be made
 * @param base The base mem address for the segment.
 * @param limit The top mem address the segment is allowed to reach
 * @param access Flags for the GDT to identify access
 * @param granularity The least significant bits should be 1111 to allow the limit not to change while the 2 bits after that should be 0s as GDT requires and the most significant bits are granularity flags and size flags.
 */
void create_gdt_entry(unsigned int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char granularity){
    gdt_entries[index].limit_low = limit & 0xFFFF;
    gdt_entries[index].limit_high_and_flags = (limit >> 16) & 0x0F;

    gdt_entries[index].base_low = base & 0xFFFF;
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high = (base >> 24) & 0xFF;

    gdt_entries[index].access = access;
    gdt_entries[index].limit_high_and_flags |= granularity;
}

/** internal create_gdt_entry
 * Creates a gdt entry at an index with page granularity and 32 bit mode.
 * 0xCF -> 1100 (Granularity on, 32 bit mode) 1111 (Keep limit the same)
 * 
 * @param index The index for the gdt_entry to be made
 * @param base The base mem address for the segment.
 * @param limit The top mem address the segment is allowed to reach
 * @param access Flags for the GDT to identify access
 */
void create_gdt_entry_default_granularity(unsigned int index, unsigned int base, unsigned int limit, unsigned char access){
    create_gdt_entry(index, base, limit, access, 0xCF);
}

void setup_gdt(){
    gdt_ptr.offset = (int) &gdt_entries;
    gdt_ptr.size = sizeof(struct gdt_entry) * 3 - 1;

    create_gdt_entry(0, 0, 0, 0, 0); // Null descriptor
    create_gdt_entry_default_granularity(1, 0, 0xFFFFFFFF, 0x9A); // Code segment
    create_gdt_entry_default_granularity(2, 0, 0xFFFFFFFF, 0x92); // Data segment

    debug_writeln("Flushing");
    gdt_flush((unsigned int) &gdt_ptr);
}