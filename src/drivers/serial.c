#include "port_io.h" 
#include "serial.h"
#include "vga_text.h"

void serial_port_configure_baud_rate(uint16_t com, uint16_t divisor){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com), 0x80); // 0x80 -> 1000 0000 Set DLAB to tell the serial controller to expect highest first then lowest.
    port_byte_out(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
    port_byte_out(SERIAL_DATA_PORT(com), divisor & 0xFF);
}

void serial_port_configure_line_default(uint16_t com){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

bool is_serial_port_fifo_trasmit_empty(uint16_t com){
    return port_byte_in(SERIAL_LINE_STATUS_PORT(com)) & 0x20; // 0x20 -> 0010 0000 5th bit checking!
}

void serial_write_char(uint16_t com, uint8_t c){
    while(is_serial_port_fifo_trasmit_empty(com) == 0);

    port_byte_out(SERIAL_DATA_PORT(com), c);
}

void init_serial_port_default(uint16_t com){
    serial_port_configure_baud_rate(com, 3);
    serial_port_configure_line_default(com);
}

void serial_write(uint16_t com, char* str){
    while(*str != 0){
        serial_write_char(com, *str);
        ++str;
    }
}

void serial_writeln(uint16_t com, char* str){
    serial_write(com, str);
    serial_write(com, "\n");
}