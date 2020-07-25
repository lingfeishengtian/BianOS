#include "../drivers/serial.h"

void initialize_serial_debugging(){
	init_serial_port_default(SERIAL_COM1_PORT);
}

void debug_write(char* str){
    serial_write(SERIAL_COM1_PORT, str);
}

void debug_writeln(char* str){
    serial_writeln(SERIAL_COM1_PORT, str);
}