global gdt_flush        ;allow our code to be accessed by c

section .text           ;start code!
gdtr DW 0 ; For limit storage
     DD 0 ; For base storage
gdt_flush:
    mov eax, [esp + 4]
    mov [gdtr + 2], eax
    mov ax, [esp + 8]
    hlt
    mov [gdtr], ax
    lgdt [gdtr]

    ret
    ;lgdt [gdt_ptr]      ;load our gdt_ptr from our gdt.h file
    
    jmp 0x08:flush      ;0x08 is the code segment register in the gdt -> time to do a FAR jump!

flush:
    hlt
    mov ax, 0x10        ;0x10 is our data segment register in the gdt
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov fs, ax

    ret
