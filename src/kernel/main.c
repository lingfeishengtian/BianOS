#include "../drivers/vga_text.h"
#include "debugger.h"
#include "gdt/gdt.h"

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

// Start here
int main(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.\n");

	initialize_serial_debugging();
	debug_writeln("Serial debugging initialized.");
	print("Serial debugging with COM1 port has been initialized.\n", GREEN, BLACK);

	printd("Initializing GDT...");
	debug_writeln("Starting GDT init process.");
	setup_gdt();
	debug_writeln("Completed GDT init process.");

	return 0;
}
