extern interrupt_handler

section .text

%macro INT_HANDLER_NO_ERR_CODE 1
interrupt_handler_%1:
    push DWORD 0
    push DWORD %1
    jmp generic_handler
%endmacro

%macro INT_HANDLER_WITH_ERR_CODE 1
interrupt_handler_%1:
    push DWORD %1
    jmp generic_handler
%endmacro

generic_handler:
    pusha
    call interrupt_handler
    popa
    add esp, 8
    iret

INT_HANDLER_NO_ERR_CODE 0
INT_HANDLER_NO_ERR_CODE 1
INT_HANDLER_NO_ERR_CODE 2
INT_HANDLER_NO_ERR_CODE 3
INT_HANDLER_NO_ERR_CODE 4
INT_HANDLER_NO_ERR_CODE 5
INT_HANDLER_NO_ERR_CODE 6
INT_HANDLER_NO_ERR_CODE 7
INT_HANDLER_WITH_ERR_CODE 8