#include "int_handler.h"
#include "../../drivers/port_io.h"
#include "../../drivers/vga_text.h"
#include "../../drivers/hardware/keyboard.h"
#include "../debugger.h"

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, unsigned int interrupt, __attribute__((unused)) struct stack_state stack){
    if(interrupt == 33){
        // Print the typed text onto the screen
        char str[2];
        str[0] = keyboard_scan_code_to_ascii(read_scan_code());
        pic_eoi(interrupt);
        printd(str);
    }
}

void pic_eoi(int interrupt){
    // Verify the PIC_EOI is needed
    if(interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT){
        return;
    }

    // The slave PIC only needed when the interrupt for the slave is called
    if(interrupt >= PIC2_START_INTERRUPT){
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    }
    // The master PIC is always needed when PIC interrupt is called
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}