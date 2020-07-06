#include "framebuffer.h"

unsigned char * const video_buffer = (unsigned char *) 0x000B8000;

void print_char(unsigned int i, char c, enum Colours tc, enum Colours bg){
	video_buffer[i] = c;
	video_buffer[i + 1] = ((bg & 0x0F) << 4) | (tc & 0x0F);
}
