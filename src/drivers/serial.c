#include "port_io.h" 
#include "serial.h"
#include "vga_text.h"

void serial_port_configure_baud_rate(unsigned short com, unsigned short divisor){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com), 0x80); // 0x80 -> 1000 0000 Set DLAB to tell the serial controller to expect highest first then lowest.
    port_byte_out(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
    port_byte_out(SERIAL_DATA_PORT(com), divisor & 0xFF);
}

void serial_port_configure_line_default(unsigned short com){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int is_serial_port_fifo_trasmit_empty(unsigned short com){
    return port_byte_in(SERIAL_LINE_STATUS_PORT(com)) & 0x20; // 0x20 -> 0010 0000 5th bit checking!
}

void serial_write_char(unsigned short com, unsigned char c){
    while(is_serial_port_fifo_trasmit_empty(com) == 0);

    port_byte_out(SERIAL_DATA_PORT(com), c);
}

void init_serial_port_default(unsigned short com){
    serial_port_configure_baud_rate(com, 3);
    serial_port_configure_line_default(com);
}