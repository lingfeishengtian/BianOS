#include "../drivers/vga_text.h"
#include "../drivers/hardware/keyboard.h"
#include "debugger.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "../grub_headers/multiboot.h"

// // Testing scrolling
// void test(){
// 	printd("TEST\nttt");
// 	printd("oof\n");
// 	for(int i = 0; i < 30; ++i){
// 		char* str = "ftkynormpgsyghwljsksjtccpbdjasokwkfzjivmnklxhedmjtixywuwtfvvwpplhkmjssyrhmrgseab"; 
// 		str[0] = i + 48;
// 		str[79] = i + 49;
// 		printd(str);
// 	}
// }

int main(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.\n");

	//initialize_serial_debugging();
	debug_writeln("Serial debugging initialized.");
	print("Serial debugging with COM1 port has been initialized.\n", GREEN, BLACK);

	printd("Initializing GDT...\n");
	debug_writeln("Starting GDT init process.");
	setup_gdt();
	debug_writeln("Completed GDT init process.");

	printd("Initializing IDT...\n");
	setup_idt();

	if(register_interrupt(33, keyboard_interrupt) == 1){
		printd("An error occured while trying to setup your keyboard driver!.");
	}
	
	return 0;
}

typedef void (*call_module_t) (void);

// Initialize the serial debugger, gdt, idt, etc.
int module_main(unsigned int mbinfo){
	main();
	debug_writeln("Starting module code.");
	mbinfo += 0xC0000000;
	module_t* modules = (module_t*) (((multiboot_info_t*) mbinfo)->mods_addr + 0xC0000000); 
    unsigned int address_of_module = modules->mod_start + 0xC0000000;
	call_module_t start_program = (call_module_t) address_of_module;
    start_program();
	return 0;
}
