#include "vga_text.h"
#include "port_io.h"

// Start init of private internal functions

/** cursor_toggle:
 *
 * Internal function: this function will probably not be used
 *
 * Toggles whether or not the cursor should be displayed. Takes in a 1 byte of data and uses bitwise and 0x1 to imitate boolean value.
 * Cursor will appear at an unknown location when toggled.
 *
 * @param t Enable or disable. 0 for disable, 1 for enable.
 */
void cursor_toggle(unsigned char t);

/** cursor_move:
 *
 * Internal function: cursor location is used to determine where the next print function will place the strings passed
 *
 * Moves cursor to a specified location.
 *
 * @param pos The position cursor should travel to.
 */
void cursor_move(unsigned short pos);

/** get_cursor_loc:
 * Get cursor location
 *
 * @return Returns a 16 bit location
 */
short get_cursor_loc();

/** scroll:
 * Shifts all text up a row.
 */
void scroll();

// Give all functions a purpose

void set_char(unsigned int i, char c, enum Colours tc, enum Colours bg){
	unsigned char * const video_buffer = (unsigned char *) VIDEO_BUFFER;

	video_buffer[i] = c;
	video_buffer[i + 1] = ((bg & 0x0F) << 4) | (tc & 0x0F);
}

char get_char(unsigned int loc){
	unsigned char * const video_buffer = (unsigned char *) VIDEO_BUFFER;
	
	return video_buffer[loc];
}

void cursor_toggle(unsigned char t){
	if(t & 0x1){
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x0E);
		port_byte_out(VGA_INDEX, CURSOR_END_REG);
		port_byte_out(VGA_DATA, 0x0F);
	}else{
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x20);
	}

}

void cursor_move(unsigned short pos){
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_HIGH);
	port_byte_out(VGA_DATA, (pos & 0xFF00) >> 8);
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_LOW);
	port_byte_out(VGA_DATA, (pos & 0xFF));
}

short get_cursor_loc(){
	short pos = 0;
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_LOW);
	pos |= port_byte_in(VGA_DATA);
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_HIGH);
	pos |= port_byte_in(VGA_DATA) << 8;
	return pos;
}

void clr_screen(){
	cursor_toggle(1);

	for(int i = 0; i < ROWS * COLS; ++i){
		set_char(i * 2, 0, WHITE, BLACK);
	}

	cursor_move(0);
}

void scroll(){
	for(int i = 1; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			const unsigned int pos = (i * COLS + j) * 2;
			const unsigned char color = get_char(pos + 1);
			set_char(pos - COLS * 2, get_char(pos), color & 0x0F, color >> 4);

			if(i == ROWS - 1){
				set_char(pos, 0, WHITE, BLACK);
			}
		}
	}

	const short cursor_pos = get_cursor_loc();
	cursor_move(cursor_pos - COLS);
}

void print(char* str, enum Colours tc, enum Colours bg){
	short initial_pos = get_cursor_loc() * 2;
	unsigned int i = 0;

	while(str[i] != 0){
		if(initial_pos >= COLS * ROWS * 2){
			scroll();
			initial_pos -= COLS * 2;
		}

		if(str[i] == '\n'){
			//TODO: Is there a better way to do this?
			initial_pos = (initial_pos + COLS * 2) - (initial_pos % (COLS * 2));
		}else{
			set_char(initial_pos, str[i], tc, bg);
			initial_pos += 2;
		}

		i++;
	}

	cursor_move(initial_pos / 2);
}

void printd(char* str){
	print(str, LIGHT_GREY, BLACK);
}
