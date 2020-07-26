global gdt_flush        ;allow our code to be accessed by c
extern debug_writeln    ;serial write a debug message
extern gdt_ptr          ;tell nasm our gdt_ptr is somewhere else

section .data
    flush_finish_msg db 'Flushed cs segment register through far jump', 0

section .text           ;start code!
gdt_flush:
    lgdt [gdt_ptr]      ;load our gdt_ptr from our gdt.h file
    mov ax, 0x10        ;0x10 is our data segment register in the gdt
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov fs, ax

    jmp 0x08:flush      ;0x08 is the code segment register in the gdt -> time to do a FAR jump!

flush:
    push flush_finish_msg   ;push the message into the stack
    call debug_writeln      ;call c method to print the message
    add esp, 4              ;put the stack back to the proper position

    ret
