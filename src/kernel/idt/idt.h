/** The IDT
 * Similar to the GDT, but for interrupts.
 */
#include "pic/pic.h"

/** idt:
 * size:
 * short -> 2 bytes
 * The size of the whole IDT - 1
 * 
 * address:
 * int -> 4 bytes
 * The address of where the whole IDT table starts
 */
struct idt{
    unsigned short size;
    unsigned int address;
} __attribute__ ((packed));

/** idt_entry:
 * entry_address_low:
 * short -> 2 bytes
 * The lower 16 bits of the 32 bit address of the interrupt handler.
 * 
 * selector:
 * short -> 2 bytes
 * The selector segment address offset in the GDT
 * 
 * zero:
 * char -> 1 byte
 * Reserved
 * 
 * type_attr:
 * char -> 1 byte
 * The interrupt table entry's attributes.
 * View the table in idt.c's function create_idt_entry()
 * 
 * entry_address_high:
 * short -> 2 bytes
 * The upper 16 bits of the 32 bit address of the interrupt handler.
 */
struct idt_entry{
    unsigned short entry_address_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short entry_address_high;
} __attribute__ ((packed));

/** setup_idt:
 * Setups the keyboard and idt handlers.
 */
void setup_idt();

/** register_interrupt:
 * Assign an interrupt to an interrupt handler and create an entry in the idt.
 * 
 * @param interrupt The interrupt code to assign
 * @param handler A function pointer to a handler
 * @return Returns 0 for success and 1 if the interrupt is taken or handler wasn't defined in the kernel.
 */
unsigned char register_interrupt(unsigned int interrupt, void (*handler)());