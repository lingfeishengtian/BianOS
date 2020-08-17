#include "../drivers/vga_text.h"
#include "../drivers/hardware/keyboard.h"
#include "debugger.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "../grub_headers/multiboot.h"
#include "utils/conversion.h"
#include "mem/mem.h"

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

/** kmain:
 * Initializes the GDT, IDT, and serial debugging.
 */
int kmain(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.\n");

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

	printd(hex_to_ascii((unsigned int) kmalloc(20)));
	printd("\n");
	printd(hex_to_ascii((unsigned int) kmalloc(23)));
	
	return 0;
}

typedef void (*call_module_t) (void);

/** module_main:
 * This main method is called from assembly and takes the ebx register from grub multiboot as a parameter.
 * The method calls the kernel main method to initialize some key elements of the kernel.
 * Eventually, the user program is found and called.
 * 
 * Note: Due to the higher half, every single address must be increased by 0xC0000000
 * 
 * @param mbinfo Module information
 * @return Return code
 */
int module_main(unsigned int mbinfo){
	kmain();
	debug_writeln("Starting module code.");
	mbinfo += 0xC0000000;
	module_t* modules = (module_t*) (((multiboot_info_t*) mbinfo)->mods_addr + 0xC0000000); 
    unsigned int address_of_module = modules->mod_start + 0xC0000000;
	call_module_t start_program = (call_module_t) address_of_module;
    start_program();
	return 0;
}
