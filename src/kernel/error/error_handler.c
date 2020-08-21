#include "error_handler.h"
#include "../idt/idt.h"
#include "../idt/int_handler.h"
#include "../../drivers/vga_text.h"
#include "../../utils/conversion.h"
#include "../mem/kheap.h"
#include "../../utils/string.h"

void error_handler(int interrupt, __attribute__ ((unused)) struct cpu_state cpu, __attribute__ ((unused)) struct stack_state stack){
    char* error_msg = "";
    kprintf("[KERNEL PANIC] ", RED, BLACK);

    switch (interrupt)
    {
    case 0:
        error_msg = "Attempted to divide by 0.";
        break;
    
    case 14:
        kprintf("Page fault occurred\nPAGE DUMP\nError Code: %x", RED, BLACK, stack.error_code);
        break;

    default:
        error_msg = "Undefined error.";
        break;
    }

    kprintf(error_msg, RED, BLACK);
    panic();
}

void panic(){
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