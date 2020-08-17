global gdt_flush        ;allow our code to be accessed by c

section .text           ;start code!
gdt_flush:
    cli
    mov eax, [esp + 4]
    lgdt [eax]
    sti                 ;load our gdt_ptr from our gdt.h file
    
    mov ax, 0x10        ;0x10 is our data segment register in the gdt
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov fs, ax

    jmp 0x08:.flush      ;0x08 is the code segment register in the gdt -> time to do a FAR jump!

.flush:
    ret
