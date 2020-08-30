global loader					;entry point for ELF

extern module_main
extern kernel_virtual_start
extern kernel_virtual_end
extern kernel_physical_end
extern bss_start
extern bss_end
extern bss_size

MAGIC 			equ 0x1BADB002            		;this magic number is required for GRUB to verify the boot
ALIGN_MODULES   equ 0x00000001      			;tell GRUB to align modules	
CHECKSUM		equ -(MAGIC + ALIGN_MODULES)	;the magic number + flags + checksum should equal 0
;declare some paging macros
KERNEL_VBASE	equ 0xC0000000					;kernel virtual base address
THREE_GB_INDEX	equ 0x00000300					;the directory index where we want to load our higher half kernel
PSE_BIT			equ 0x00000010					;enable 4 MiB
PG_BIT			equ 0x80000000					;enable paging

KERNEL_STACK	equ 8192					;establish kernel stack size in bytes

section .pg_bss		 ; in the linker script, this is in the lower half of virtual memory
alignb 4096          ; page align the page directory and tables
page_directory:
  resd 1024          ; reserve 1024 DWORDs for our page table pointers
lowmem_pt:
  resd 1024          ; lowmem identity mappings (grub & bios, etc)
kernel_pt:
  resd 1024          ; our kernel page table mappings 
section .bss					;use section bss in order to optimize and conserve space
align 4
kernel_stack:					;point to beginning of stack
	resb KERNEL_STACK			;reserve space for stack

section .__mbHeader
align 4							;grub requires aligned by 4 offsets to detect the headers
	dd MAGIC					;load headers in
	dd ALIGN_MODULES
	dd CHECKSUM	

section .data
multiboot_info:					;save some space for our multiboot info
	dd 0

section .text
loader:							;entry point defined earlier
	mov [multiboot_info - KERNEL_VBASE], ebx		;save our multiboot info

	mov ecx, bss_size								;zero the page directory bss		
	xor al, al
	mov edi, bss_start 
	rep stosb

	mov eax, lowmem_pt								;set page dir[0] to lowmem page table
	mov [page_directory], eax
	or dword [page_directory], 3 					;mark the PT as present

	mov eax, 0										;identity map starting from 0

	.lowmem:
	mov ecx, eax
	shr ecx, 12     								;divide our current address by 0x1000
	and ecx, 0x3ff         				 			;current addr % 1024
	mov [lowmem_pt+ecx*4], eax 						;copy our physical address to the page entry
	or dword [lowmem_pt+ecx*4], 3 					;write our permissions (present, etc)

	add eax, 0x1000 								;move on to the next page
	cmp eax, 0x0010F000 							;are we done with lowmem? 
	jl .lowmem

	mov edx, KERNEL_VBASE							;higher half kernel time!
	shr edx, 22          							;find which page table we need to use

	mov eax, kernel_pt
	mov [page_directory+edx*4], eax					;page dir[768] = kernel_pt
	or dword [page_directory+edx*4], 3 				;mark the PT as present

	mov eax, KERNEL_VBASE 							;the kernel's current virtual start
	.higher:										;same process as lower memory
	mov ecx, eax
	shr ecx, 12
	and ecx, 0x3ff

	mov ebx, eax 
	sub ebx, KERNEL_VBASE 							;find the physical address
	mov [kernel_pt+ecx*4], ebx
	or dword [kernel_pt+ecx*4], 3

	add eax, 0x1000    
	cmp eax, (kernel_virtual_end + 0x000C0000) 		;finished??????
	jl .higher

	mov eax, page_directory
	mov cr3, eax 									;load CR3 with our page directory

	mov eax, cr0
	or eax, PG_BIT
	mov cr0, eax 									;enable paging! time to pray...
	
	;far jump to avoid reference relative jump
	lea ecx, [higher_kernel_entry]
	jmp ecx

higher_kernel_entry:
	mov esp, kernel_stack + KERNEL_STACK	;setup stack for programming in c: point stack to top (stack grows downward)

	push dword [multiboot_info]

	call module_main						;call module_main

.loop:
	jmp .loop								;loop forever to hang the OS just in case the kernel returns