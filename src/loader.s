global loader					;entry point for ELF

MAGIC 		equ 0x1BADB002            	;this magic number is required for GRUB to verify the boot
MODE_FLAG	equ 0x0	              	  	;this flag tells grub we want to go to protected mode
CHECKSUM	equ -MAGIC			;the magic number + flags + checksum should equal 0

section .text:					;code section
align 4						;grub requires aligned by 4 offsets to detect the headers
	dd MAGIC				;load headers in
	dd MODE_FLAG
	dd CHECKSUM	

loader:						;entry point defined earlier
	mov eax, 0xFFFAC310			;load number to eax register
.loop:
	jmp .loop				;loop forever to hang the OS
