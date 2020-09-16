#include "keyboard.h"
#include "../port_io.h"
#include "../vga_text.h"
#include "../../kernel/idt/pic/pic.h"

bool shift_held = false;
char ascii[256] =
{
	0x0, 0x0, '1', '2', '3', '4', '5', '6',	
	'7', '8', '9', '0', '-', '=', 0x0, 0x0,	
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',	
	'o', 'p', '[', ']', '\n', 0x0, 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	
	'\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0x0, '*',	
	0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,	
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',	
	'8', '9', '-', '4', '5', '6', '+', '1',	
	'2', '3', '0', '.'			
};

void keyboard_interrupt(int interrupt){
    // Print the typed text onto the screen
    pic_eoi(interrupt);
	
    kprintf("%c", WHITE, BLACK, keyboard_scan_code_to_ascii(read_scan_code()));
}

uint8_t read_scan_code(void){
    return port_byte_in(KBD_DATA_PORT);
}

char capitalize(char c){
	char int_capital_map[10] =
	{')', '!', '@', '#', '$', '%', '^', '&', '*', '('};

	if(c >= 97 && c <= 122){
		return c - 32;
	} else if(c >= 48 && c <= 57){
		return int_capital_map[c - 48];
	}

	return c;
}

uint8_t keyboard_scan_code_to_ascii(uint8_t scan_code){
	if(scan_code == DELETE){
		kdelete();
	}else{
		if(scan_code == L_SHIFT_KEY_DOWN || scan_code == R_SHIFT_KEY_DOWN){
			shift_held = true;
		} else if(scan_code == L_SHIFT_KEY_UP || scan_code == R_SHIFT_KEY_UP) {
			shift_held = false;
		}

		return shift_held ? capitalize(ascii[scan_code]) : ascii[scan_code];
	}
	return 0;
}