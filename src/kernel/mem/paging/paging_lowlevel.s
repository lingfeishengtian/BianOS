global switch_page_directory
section .text
switch_page_directory:
    push ecx                    ;save the ecx register before its overwritten
    mov ecx, [esp + 8]          ;sinced we pushed ecx, we find the the address of the page directory at esp + 8
    sub ecx, 0xC0000000         ;assuming we are switching page directories from the kernel, subtract 0xC0000000 to get physical address
    mov cr3, ecx                ;switch page dir
    pop ecx                     ;return ecx register
    ret                         ;return