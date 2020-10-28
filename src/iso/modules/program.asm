 ; set eax to random number to read from the log afterwards
bits 32

section .text
start:
or [0xC00B8001], BYTE 0x20 ;module makes first letter of vga text background green
ret