#include "error_handler.h"
#include "../idt/idt.h"
#include "../idt/int_handler.h"
#include "../../drivers/vga_text.h"

void internal_dump_cpu(cpu_state_t cpu){
    kprintf("\nCPU DUMP\n", LIGHT_BLUE, BLACK);
    kprintf("EAX: %x\tEBX: %x\nECX: %x\tEDX: %x\nEAX: %x\tEBX: %x\nESP: %x\tEBP: %x\nESI: %x\tEDI:%x\n", 
            RED, BLACK,
            cpu.eax, 
            cpu.ebx, 
            cpu.ecx, 
            cpu.edx,
            cpu.esp,
            cpu.ebp,
            cpu.esi,
            cpu.edi);
}

void dump_cpu(){
    asm("pusha");
    asm("call internal_dump_cpu");
    asm("popa");
}

void error_handler(int interrupt, cpu_state_t cpu, struct stack_state stack){
    char* error_msg = "";
    kprintf("[KERNEL PANIC] ", RED, BLACK);

    switch (interrupt)
    {
    case 0:
        error_msg = "Attempted to divide by 0.";
        break;
    
    case 14:
        ;
        uint32_t bad_address;
        asm("movl %%cr2,%0" : "=r"(bad_address));
        kprintf("Page fault occurred.\n", RED, BLACK);
        kprintf("PAGE DUMP\n", LIGHT_BLUE, BLACK);

        uint32_t err_code = stack.error_code; 
        if((err_code >> 2) & 0x1)
            kprint_str("User process");
        else
            kprint_str("Supervisory process");

        kprint_str(" tried to ");

        if((err_code >> 1) & 0x1)
            kprint_str("write to ");
        else
            kprint_str("read");

        kprint_str(" a ");

        if(err_code & 0x1)
            kprint_str("page and caused a protection fault.");
        else
            kprint_str("non-present page entry.");

        kprintf("\nError occurred at address: %x", 
                LIGHT_GREY, 
                BLACK,
                bad_address);

        error_msg = "[KERNAL PANIC] Unrecoverable error.";
        break;

    default:
        error_msg = "Undefined error.";
        break;
    }

    kprintf(error_msg, RED, BLACK);

    internal_dump_cpu(cpu);
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