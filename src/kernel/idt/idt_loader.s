global load_idt ;make load_idt accessible from c

section .text
load_idt:
    mov eax, [esp + 4]  ;move the pointer from the parameter into the eax register
    lidt [eax]          ;tell the cpu to use the new idt at the address specified in eax
    ret                 ;return