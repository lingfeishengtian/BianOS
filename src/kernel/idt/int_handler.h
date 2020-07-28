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

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);