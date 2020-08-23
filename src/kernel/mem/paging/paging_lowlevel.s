global disable_pse_and_paging
global enable_paging
global switch_page_directory
extern kprint_str

KERNEL_VBASE	equ 0xC0000000					;kernel virtual base address
PSE_BIT			equ 0x00000010					;enable 4 MiB
PG_BIT			equ 0x80000000					;enable paging

section .data
    msg dd "Test msg", 0

section .text
disable_pse_and_paging:

    push ecx
    mov ecx, cr0                                   ; Set the A-register to control register 0.
    and ecx, 01111111111111111111111111111111b     ; Clear the PG-bit, which is bit 31.
    
    mov cr0, ecx


    mov ecx, cr4
    xor ecx, PSE_BIT
    mov cr4, ecx
    pop ecx
    ret

enable_paging:
    push ecx
    mov ecx, cr0
    or ecx, PG_BIT
    mov cr0, ecx
    pop ecx
    ret

switch_page_directory:
    push ecx
    mov ecx, [esp + 4]
    sub ecx, KERNEL_VBASE
    mov cr3, ecx
    pop ecx
    ret