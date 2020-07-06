#include "framebuffer.h"

void print_char(unsigned int i, char c, enum Colours tc, enum Colours bg){
	unsigned char * const video_buffer = (unsigned char *) VIDEO_BUFFER;

	video_buffer[i] = c;
	video_buffer[i + 1] = ((bg & 0x0F) << 4) | (tc & 0x0F);
}
