#include "idt.h"
#include "pic/pic.h"
#include "int_handler.h"
#include "../debugger.h"
#include "../../drivers/port_io.h"

struct idt_entry idt_entries[256];
struct idt idt_ptr;

// Use idt loader and interrupt handler generated from assembly
extern void interrupt_handler_33(void);
extern int load_idt(void*); 

/** internal create_idt_entry:
 * Creates a new IDT entry in the specified interrupt code.
 * 
 * @param int_code The interrupt code(index) in the idt_entries array to create the entry
 * @param entry The entry address of the handler(from assembly file)
 */
void create_idt_entry(int int_code, unsigned int entry){
    // Store the address in the struct
    idt_entries[int_code].entry_address_low = entry & 0xFFFF;
    idt_entries[int_code].entry_address_high = (entry >> 16) & 0xFFFF;

    // Default values
    idt_entries[int_code].selector = 0x08;  //Code segment selector in the GDT
    idt_entries[int_code].type_attr = 0x8E; // 0x8E -> 1000 1110
    idt_entries[int_code].zero = 0;

    /** 
     *  7                               0
     *  +---+---+---+---+---+---+---+---+
     *  | P |  DPL  | S |    GateType   |
     *  | 1 | 0   0 | 0 | 1  1  1  0    |
     *  +---+---+---+---+---+---+---+---+
     * P: 0 for unused interrupts, but we are using it
     * DPL: Descriptor permission level -> Ring 0 is what we set for kernel level
     * S: Storage segment -> 0 for interrupt and trap gates
     * GateType: 1110 is 32 Bit Interrupt Gate
     */
}

unsigned char register_interrupt(unsigned int interrupt, void (*handler)()){
    if(idt_entries[interrupt].selector & 0x08) return 1;
    switch (interrupt)
    {
    case 33:
        create_idt_entry(interrupt, (unsigned int) interrupt_handler_33);
        break;
    
    default:
        return 1;
    }
    register_handler(interrupt, handler);
    return 0;
}

void setup_idt(){
    // Initialize IDT
    idt_ptr.address = (unsigned int) &idt_entries;
    idt_ptr.size = sizeof(struct idt_entry) * 256 - 1;

    // Load IDT through assembly and ensure the IDT was properly loaded
    int ptr = load_idt(&idt_ptr);
    if(ptr == (int) &idt_ptr){
        debug_writeln("IDT successfully loaded!");
    }

    // Remap PIC
    pic_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT); // Remap PIC to 0x20 and 0x28
}