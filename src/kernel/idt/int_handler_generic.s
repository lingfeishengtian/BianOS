extern interrupt_handler            ;handle interrupts in our c file

section .text                       

;If the interrupt does not have an error code, we push 0 as an error code
%macro INT_HANDLER_NO_ERR_CODE 1    ;make nasm do all the work for us cause i'm lazy 
global interrupt_handler_%1
interrupt_handler_%1:
    push DWORD 0                    ;push 0 on the stack to subsitute as an error code
    push DWORD %1                   ;push the interrupt code on the stack
    jmp generic_handler
%endmacro

;If the interrupt does have an error code
%macro INT_HANDLER_WITH_ERR_CODE 1
global interrupt_handler_%1
interrupt_handler_%1:
    push DWORD %1                   ;push the interrupt code on the stack
    jmp generic_handler
%endmacro

;a gerneric interrupt handler that saves the cpu registers and pops them after our c file's interrupt handler completes
generic_handler:
    pusha                           ;pushes all registers
    call interrupt_handler          ;call our c function
    popa                            ;pops the registers back
    add esp, 8                      ;remove interrupt code and error code from the stack
    iretd                           ;let iret pop eflags, cs, and ip

INT_HANDLER_NO_ERR_CODE 33          ;keyboard interrupt handler