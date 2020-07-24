#include "../drivers/vga_text.h"
#include "../drivers/serial.h"

// Testing scrolling
void test(){
	printd("TEST\nttt");
	printd("oof\n");
	for(int i = 0; i < 30; ++i){
		char* str = "ftkynormpgsyghwljsksjtccpbdjasokwkfzjivmnklxhedmjtixywuwtfvvwpplhkmjssyrhmrgseab"; 
		str[0] = i + 48;
		str[79] = i + 49;
		printd(str);
	}
}

void initialize_serial_debugging(){
	init_serial_port_default(SERIAL_COM1_PORT);
	serial_write_char(SERIAL_COM1_PORT, 't');
	serial_write_char(SERIAL_COM1_PORT, '\n');
}

// Start here
int main(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.");
    printd("operating system"); 

	initialize_serial_debugging();

	return 0;
}
