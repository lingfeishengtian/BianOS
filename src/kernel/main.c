#include "../drivers/vga_text.h"
#include "../drivers/hardware/keyboard.h"
#include "debugger.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "../grub_headers/multiboot.h"
#include "../utils/conversion.h"
#include "mem/kheap.h"
#include "error/error_handler.h"

/** kmain:
 * Initializes the GDT, IDT, and serial debugging.
 */
int kmain(){
	clr_screen();
	printd("Welcome to BianOS. CURSOR is enabled by default.\n");

	initialize_serial_debugging();
	debug_writeln("Serial debugging initialized.");
	print("Serial debugging with COM1 port has been initialized.\n", GREEN, BLACK);

	printd("Initializing GDT...\n");
	debug_writeln("Starting GDT init process.");
	setup_gdt();
	debug_writeln("Completed GDT init process.");

	printd("Initializing IDT...\n");
	setup_idt();

	if(register_interrupt(33, keyboard_interrupt, false) == 1){
		printd("An error occured while trying to setup your keyboard driver!.");
	}
	initialize_error_handling();
	
	char* f = (char*) 0xB0000000;
	f[0] = 'f';

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
int module_main(uint32_t mbinfo){
	mbinfo += 0xC0000000;
	module_t* modules = (module_t*) (((multiboot_info_t*) mbinfo)->mods_addr + 0xC0000000); 
    uint32_t address_of_module = modules->mod_start + 0xC0000000;
	call_module_t start_program = (call_module_t) address_of_module;
	kmain();
  	start_program();
	return 0;
}
