#include "pic/pic.h"

/** 
 * This struct will be the state of the cpu before the interrupt is handled. The programs running the interrupt assume all the registers will be the same afterwards.
 * This struct contains the contents pushed by pusha
 */
struct cpu_state{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} __attribute__ ((packed));

/**
 * This struct contains the contents of the stack when the interrupt is called.
 * See page 6-13 on the Intel documentation(https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf)
 */
struct stack_state{
    uint32_t error_code;
    uint32_t eip, cs, eflags;
} __attribute__ ((packed));

/** interrupt_handler:
 * Handles all interrupts that are called from the IDT table. This function is called from the specific idt
 * handlers created in the assembly file.
 * 
 * @param cpu All of the cpu registers saved from pusha. WILL NOT BE USED BECAUSE THESE WILL BE POPPED!!
 * @param interrupt The interrupt code that was called
 * @param stack Information pushed by the cpu
 */
void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, int interrupt, __attribute__((unused)) struct stack_state stack);

/** register_handler:
 * Assign an interrupt to an interrupt handler.
 * 
 * @param interrupt The interrupt code to assign
 * @param handler A function pointer to a handler
 * @return Returns 0 for success and 1 if the interrupt is taken.
 */
void register_handler(uint32_t interrupt, void (*handler)());