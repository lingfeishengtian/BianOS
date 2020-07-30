/** The IDT
 * Similar to the GDT, but for interrupts.
 */

// PIC has two parts, PIC1 and PIC2. We remap them to the following interrupts
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28

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