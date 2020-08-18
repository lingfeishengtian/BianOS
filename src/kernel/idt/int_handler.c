#include "int_handler.h"
#include "../../drivers/port_io.h"
#include "../../drivers/vga_text.h"
#include "../debugger.h"

void (*interrupt_handlers[256]) ();

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, int interrupt, __attribute__((unused)) struct stack_state stack){
    interrupt_handlers[interrupt]();
}


void register_handler(unsigned int interrupt, void (*handler)()){
    interrupt_handlers[interrupt] = handler;
}