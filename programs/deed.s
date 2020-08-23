 ; set eax to random number to read from the log afterwards
bits 32

section .text
start:
mov eax, 0xDEADC0DE

; enter infinite loop
jmp $