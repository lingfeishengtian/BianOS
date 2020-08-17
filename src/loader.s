global loader					;entry point for ELF

[extern module_main]

extern kernel_virtual_start
extern kernel_virtual_end
extern kernel_physical_start
extern kernel_physical_end

MAGIC 			equ 0x1BADB002            		;this magic number is required for GRUB to verify the boot
ALIGN_MODULES   equ 0x00000001      			;tell GRUB to align modules	
CHECKSUM		equ -(MAGIC + ALIGN_MODULES)	;the magic number + flags + checksum should equal 0
;declare some paging macros
KERNEL_VBASE	equ 0xC0000000					;kernel virtual base address
THREE_GB_INDEX	equ 0x00000300					;the directory index where we want to load our higher half kernel
PSE_BIT			equ 0x00000010					;enable 4 MiB
PG_BIT			equ 0x80000000					;enable paging

KERNEL_STACK	equ 8192					;establish kernel stack size in bytes

;section .data
;align 4096
;global TMP_PAGE_DIRECTORY
;TMP_PAGE_DIRECTORY:
;Identity map first 4 MB of memory and 3 gib memory
;Paging table not needed because of 4 MiB page size
	;dd 0x83									;binary 10000011 To set page size to 4 MiB, R/W to true, Present to true
	;times(THREE_GB_INDEX - 1) dd 0			;fill the directory until 1 before the 3 gb index
	;dd 0x83									;mark the higher half kernel page
	;times(1024 - THREE_GB_INDEX - 1) dd 0	;fill the rest of the table

section .bss					;use section bss in order to optimize and conserve space
align 4
kernel_stack:					;point to beginning of stack
	resb KERNEL_STACK			;reserve space for stack

section .text					;code section
align 4							;grub requires aligned by 4 offsets to detect the headers
	dd MAGIC					;load headers in
	dd ALIGN_MODULES
	dd CHECKSUM	

;low_kernel_entry:
	;set page directory
	;mov ecx, (TMP_PAGE_DIRECTORY - KERNEL_VBASE)
	;mov cr3, ecx

	;enable 4mib pages
	;mov ecx, cr4
	;or ecx, PSE_BIT
	;mov cr4, ecx

	;set PG bit to enable paging
	;mov ecx, cr0
	;or ecx, PG_BIT
	;mov cr0, ecx

	;far jump to avoid reference relative jump
	;lea ecx, [higher_kernel_entry]
	;jmp ecx

;higher_kernel_entry:
	;unmap first 4mib in the pdt also flush tlb
	;mov dword [TMP_PAGE_DIRECTORY], 0
	;invlpg [0]

mov esp, kernel_stack + KERNEL_STACK	;setup stack for programming in c: point stack to top (stack grows downward)

loader:							;entry point defined earlier
	add esp, 4
	push ebx

	call module_main			;call module_main

.loop:
	jmp .loop				;loop forever to hang the OS
