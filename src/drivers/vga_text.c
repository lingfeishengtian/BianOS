#include "vga_text.h"
#include "port_io.h"

void print_char(unsigned int i, char c, enum Colours tc, enum Colours bg){
	unsigned char * const video_buffer = (unsigned char *) VIDEO_BUFFER;

	video_buffer[i] = c;
	video_buffer[i + 1] = ((bg & 0x0F) << 4) | (tc & 0x0F);
}

void cursor_toggle(unsigned char t){
	if(t & 0x1){
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x20);
	}else{
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x00);
	}

}

void cursor_move(unsigned short pos){
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_HIGH);
	port_byte_out(VGA_DATA, (pos & 0xFF00) >> 8);
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_LOW);
	port_byte_out(VGA_DATA, (pos & 0xFF));
}
