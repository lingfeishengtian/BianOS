global loader					;entry point for ELF

[extern main]

MAGIC 		equ 0x1BADB002            	;this magic number is required for GRUB to verify the boot
MODE_FLAG	equ 0x0	              	  	;this flag tells grub we want to go to protected mode
CHECKSUM	equ -MAGIC			;the magic number + flags + checksum should equal 0

KERNEL_STACK	equ 8192			;establish kernel stack size in bytes

section .bss					;use section bss in order to optimize and conserve space
align 4
kernel_stack:					;point to beginning of stack
	resb KERNEL_STACK			;reserve space for stack

section .text					;code section
align 4						;grub requires aligned by 4 offsets to detect the headers
	dd MAGIC				;load headers in
	dd MODE_FLAG
	dd CHECKSUM	

loader:						;entry point defined earlier
	mov esp, kernel_stack + KERNEL_STACK	;setup stack for programming in c: point stack to top (stack grows downward)
	call main				;call kernel main
.loop:
	jmp .loop				;loop forever to hang the OS
