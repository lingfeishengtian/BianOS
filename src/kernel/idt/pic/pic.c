#include "pic.h"
#include "../../../drivers/port_io.h"

void pic_remap(unsigned char offset1, unsigned char offset2){
    // ICW1 Initialize in cascaded mode and expect ICW4
    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // ICW2 Start sending the vector offsets
    port_byte_out(PIC1_DATA, offset1);
    port_byte_out(PIC2_DATA, offset2);

    // ICW3 Tell how the master and slave are connected
    port_byte_out(PIC1_DATA, 4); // IR2 is connected to slave
    port_byte_out(PIC2_DATA, 2); // This is slave 2

    // ICW4 Tell PIC we are in 8086/88 mode
    port_byte_out(PIC1_DATA, ICW4_8086);
    port_byte_out(PIC2_DATA, ICW4_8086);

    // Enable keyboard only
    port_byte_out(PIC1_DATA, 0xFD);
    port_byte_out(PIC2_DATA, 0xFF);

    asm("sti"); //enable interrupts
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