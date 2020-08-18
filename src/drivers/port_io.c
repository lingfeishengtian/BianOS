#include "port_io.h"

uint8_t port_byte_in(uint16_t port_addr){
	uint8_t result;
	__asm__("inb %%dx, %%al" : "=a" (result) : "d" (port_addr));
	return result;
}

void port_byte_out(uint16_t port_addr, uint8_t data){
	__asm__("outb %%al, %%dx" : : "a" (data), "d" (port_addr));
}

uint16_t port_word_in(uint16_t port_addr){
	uint16_t result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port_addr));
	return result;
}

void port_word_out(uint16_t port_addr, uint16_t data){
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port_addr));
}