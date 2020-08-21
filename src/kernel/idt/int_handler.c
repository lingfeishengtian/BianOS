#include "int_handler.h"
#include "../debugger.h"
#include "../../utils/conversion.h"

void (*interrupt_handlers[256]) ();
uint8_t should_pass_cpu[32];

void interrupt_handler(struct cpu_state cpu, int interrupt, struct stack_state stack){
    if(should_pass_cpu[interrupt / 8] >> (interrupt % 8)){
        interrupt_handlers[interrupt](interrupt, cpu, stack);
    }else{
        interrupt_handlers[interrupt](interrupt);
    }
}

void register_handler(uint32_t interrupt, void (*handler)(), bool dump_cpu){
    interrupt_handlers[interrupt] = handler;

    uint8_t dump = dump_cpu;
    dump <<= interrupt % 8;
    should_pass_cpu[interrupt / 8] |= dump;
}