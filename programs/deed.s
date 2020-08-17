 ; set eax to random number to read from the log afterwards
bits 32

section .text
start:
mov [0xC00B8000], BYTE 0x41 ;module writes A to the first value of framebuffer

; enter infinite loop
jmp $