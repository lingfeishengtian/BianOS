#include "idt.h"
#include "pic/pic.h"

#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7
#define PIC_EOI     0x20

/** 
 * This struct will be the state of the cpu before the interrupt is handled. The programs running the interrupt assume all the registers will be the same afterwards.
 * This struct contains the contents pushed by pusha
 */
struct cpu_state{
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
} __attribute__ ((packed));

/**
 * This struct contains the contents of the stack when the interrupt is called.
 * See page 6-13 on the Intel documentation(https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf)
 */
struct stack_state{
    unsigned int error_code;
    unsigned int eip, cs, eflags;
} __attribute__ ((packed));

/** interrupt_handler:
 * Handles all interrupts that are called from the IDT table. This function is called from the specific idt
 * handlers created in the assembly file.
 * 
 * @param cpu All of the cpu registers saved from pusha. WILL NOT BE USED BECAUSE THESE WILL BE POPPED!!
 * @param interrupt The interrupt code that was called
 * @param stack Information pushed by the cpu
 */
void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, unsigned int interrupt, __attribute__((unused)) struct stack_state stack);

/** pic_eoi:
 * Tell the PIC that we ended the interrupt.
 * 
 * @param interrupt The interrupt code that was recieved to verify if the pic_eoi is needed or which PICs need it
 */
void pic_eoi(int interrupt);