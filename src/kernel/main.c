#include "../drivers/vga_text.h"
#include "../drivers/hardware/keyboard.h"
#include "debugger.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "../grub_headers/multiboot.h"
#include "../utils/conversion.h"
#include "mem/kheap.h"
#include "error/error_handler.h"
#include "mem/paging/paging.h"

/** kmain:
 * Initializes the GDT, IDT, and serial debugging.
 */
int kmain(){
	kprint_str("Welcome to BianOS. CURSOR is enabled by default.\n");

	initialize_serial_debugging();
	debug_writeln("Serial debugging initialized.");
	kprintf("Serial debugging with COM1 port has been initialized.\n", GREEN, BLACK);

	kprint_str("Initializing GDT...\n");
	debug_writeln("Starting GDT init process.");
	setup_gdt();
	debug_writeln("Completed GDT init process.");

	kprint_str("Initializing IDT...\n");
	setup_idt();

	if(register_interrupt(33, keyboard_interrupt, false) == 1){
		kprint_str("An error occured while trying to setup your keyboard driver!.");
	}
	init_paging();
	initialize_error_handling();

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
int module_main(multiboot_info_t* mbinfo){
	clr_screen();
	module_t* modules = (module_t*) ((mbinfo)->mods_addr);
    uint32_t address_of_module = (uint32_t) modules->mod_start + 0xC0000000;
	kernel_placement_addr = (void *) modules->mod_end + 0xC0000000;

	kprintf("Address: %x\nMods Count: %d\nMoving kernel heap to %x!\n",
	 		RED,
			BLACK,
			address_of_module,
			mbinfo->mods_count,
			kernel_placement_addr);
	kmain();

	call_module_t start_program = (call_module_t) address_of_module;

	char* test = malloc(32);
	char* test1 = malloc(32);
	kprintf("%x\n%x", RED, BLACK, test, test1);

  	start_program();
	
	return 0;
}
