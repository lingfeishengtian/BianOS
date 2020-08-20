#include "error_handler.h"
#include "../idt/idt.h"
#include "../idt/int_handler.h"
#include "../../drivers/vga_text.h"
#include "../../utils/conversion.h"
#include "../mem/kheap.h"
#include "../../utils/string.h"

void error_handler(int interrupt, __attribute__ ((unused)) struct cpu_state cpu, __attribute__ ((unused)) struct stack_state stack){
    char* error_msg;

    switch (interrupt)
    {
    case 0:
        error_msg = "Attempted to divide by 0.";
        break;
    
    case 14:
        error_msg = concat("Page fault occurred\nPAGE DUMP\nError Code: ", hex_to_ascii(stack.error_code));
        break;

    default:
        error_msg = "Undefined error.";
        break;
    }

    panic(error_msg);
}

void panic(char* reason){
    print("[KERNEL PANIC] ", RED, BLACK);
    print(reason, RED, BLACK);

    while (true)
    {
        asm volatile ("cli");
        asm volatile ("hlt");
    }
}

void reg_interrupt_default(int interrupt){
    register_interrupt(interrupt, error_handler, true);
}

void initialize_error_handling(){
    reg_interrupt_default(0);
    reg_interrupt_default(14);
}