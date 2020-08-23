global switch_page_directory
section .text
switch_page_directory:
    push ecx
    mov ecx, [esp + 8]
    sub ecx, 0xC0000000
    mov cr3, ecx
    pop ecx
    ret