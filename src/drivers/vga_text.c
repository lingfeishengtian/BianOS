#include <stdarg.h>

#include "vga_text.h"
#include "port_io.h"
#include "../utils/conversion.h"

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
void cursor_toggle(bool t);

/** cursor_move:
 *
 * Internal function: cursor location is used to determine where the next print function will place the strings passed
 *
 * Moves cursor to a specified location.
 *
 * @param pos The position cursor should travel to.
 */
void cursor_move(uint16_t pos);

/** get_cursor_loc:
 * Get cursor location
 *
 * @return Returns a 16 bit location
 */
uint16_t get_cursor_loc();

/** scroll:
 * Shifts all text up a row.
 */
void scroll();

void set_char(uint32_t i, char c, enum Colours tc, enum Colours bg){
	uint8_t * const video_buffer = (uint8_t *) VIDEO_BUFFER;

	video_buffer[i] = c;
	video_buffer[i + 1] = ((bg & 0x0F) << 4) | (tc & 0x0F);
}

char get_char(uint32_t loc){
	uint8_t * const video_buffer = (uint8_t *) VIDEO_BUFFER;
	
	return video_buffer[loc];
}

void cursor_toggle(bool t){
	if(t){
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x0E);
		port_byte_out(VGA_INDEX, CURSOR_END_REG);
		port_byte_out(VGA_DATA, 0x0F);
	}else{
		port_byte_out(VGA_INDEX, CURSOR_START_REG);
		port_byte_out(VGA_DATA, 0x20);
	}

}

void cursor_move(uint16_t pos){
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_HIGH);
	port_byte_out(VGA_DATA, (pos & 0xFF00) >> 8);
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_LOW);
	port_byte_out(VGA_DATA, (pos & 0xFF));
}

uint16_t get_cursor_loc(){
	uint16_t pos = 0;
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_LOW);
	pos |= port_byte_in(VGA_DATA);
	port_byte_out(VGA_INDEX, CURSOR_LOCATION_HIGH);
	pos |= port_byte_in(VGA_DATA) << 8;
	return pos;
}

void clr_screen(){
	cursor_toggle(true);

	for(int i = 0; i < ROWS * COLS; ++i){
		set_char(i * 2, 0, WHITE, BLACK);
	}

	cursor_move(0);
}

void scroll(){
	for(int i = 1; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			const uint32_t pos = (i * COLS + j) * 2;
			const uint8_t color = get_char(pos + 1);
			set_char(pos - COLS * 2, get_char(pos), color & 0x0F, color >> 4);

			if(i == ROWS - 1){
				set_char(pos, 0, WHITE, BLACK);
			}
		}
	}

	const uint16_t cursor_pos = get_cursor_loc();
	cursor_move(cursor_pos - COLS);
}

void check_pos_scroll(uint16_t *pos){
	if(*pos >= COLS * ROWS * 2){
		scroll();
		*pos -= COLS * 2;
	}
}

void kprintf_internal(char* str, char c, uint16_t *pos, enum Colours tc, enum Colours bg){
	if(c){
		check_pos_scroll(pos);
		if(c == '\n'){
			*pos = (*pos + COLS * 2) - (*pos % (COLS * 2));
		} else{
			set_char(*pos, c, tc, bg);
			*pos += 2;
		}
	} else {
		uint32_t i = 0;

		while(str[i] != 0){
			kprintf_internal(0, str[i], pos, tc, bg);
			++i;
		}
	}
}

void kprintf(char* str, enum Colours tc, enum Colours bg, ...){
	uint16_t initial_pos = get_cursor_loc() * 2;
	uint32_t i = 0;

	va_list ap;
	va_start(ap, bg);

	while(str[i] != 0){
		if(str[i] == '%'){
			char arg = str[++i];

			char c_arg = 0;
			char* c_ptr_arg = 0;

			switch (arg)
			{
			case 'c':
				c_arg = (char) va_arg(ap, int);
				break;
			case 's':
				c_ptr_arg = va_arg(ap, char*);
				break;
			case 'x':
				c_ptr_arg = hex_to_ascii(va_arg(ap, int));
				break;
			case 'd':
				c_ptr_arg = int_to_ascii(va_arg(ap, int));
				break;
			case '%':
				c_arg = '%';
				break;
			default:
				break;
			}

			kprintf_internal(c_ptr_arg, c_arg, &initial_pos, tc, bg);
		}else{
			kprintf_internal(0, str[i], &initial_pos, tc, bg);
		}

		i++;
	}

	va_end(ap);
	cursor_move(initial_pos / 2);
}

void kprint_str(char* str){
	kprintf(str, LIGHT_GREY, BLACK);
}
