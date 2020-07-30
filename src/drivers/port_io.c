#include "port_io.h"

unsigned char port_byte_in(unsigned short port_addr){
	unsigned char result;
	__asm__("inb %%dx, %%al" : "=a" (result) : "d" (port_addr));
	return result;
}

void port_byte_out(unsigned short port_addr, unsigned char data){
	__asm__("outb %%al, %%dx" : : "a" (data), "d" (port_addr));
}

unsigned short port_word_in(unsigned short port_addr){
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port_addr));
	return result;
}

void port_word_out(unsigned short port_addr, unsigned short data){
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port_addr));
}