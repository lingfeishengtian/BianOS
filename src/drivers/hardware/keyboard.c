#include "keyboard.h"
#include "../port_io.h"
#include "../vga_text.h"
#include "../../kernel/idt/pic/pic.h"

void keyboard_interrupt(){
    // Print the typed text onto the screen
    char str[2];
    str[0] = keyboard_scan_code_to_ascii(read_scan_code());
    pic_eoi(KEYBOARD_INTERRUPT_CODE);
    printd(str);
}

unsigned char read_scan_code(void){
    return port_byte_in(KBD_DATA_PORT);
}

unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code){
	unsigned char ascii[256] =
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

	return ascii[scan_code];
}