ENTRY(loader)			/* name of our entry point */

 /* these labels get exported to the code files */

SECTIONS{
	. = 0x00100000;

	.__mbHeader : { *(.__mbHeader) }
	.pg_bss ALIGN (0x1000):
	{
		bss_start = .;
		*(.pg_bss)
		bss_end = .;
	}

	bss_size = bss_end - bss_start;
	
	. += 0xC0000000;		/* code starts at 1MB because before that is grub & bios */

	kernel_virtual_start = .;
	kernel_physical_start = . - 0xC0000000;

	.text ALIGN (0x1000): AT(ADDR(.text)-0xC0000000)	/* align code at 4KB */
	{
		*(.text)
	}

	.rodata ALIGN (0x1000): AT(ADDR(.rodata)-0xC0000000)	/* align read only data at 4KB */
	{
		*(.rodata*)
	}

	.data ALIGN (0x1000): AT(ADDR(.data)-0xC0000000)	/* align data at 4KB */
	{
		*(.data)
	}

	.bss ALIGN (0x1000): AT(ADDR(.bss)-0xC0000000)	/* align C variables at 4KB */
	{
		*(COMMON)	/* eventually all initialized and uninitialized c variables will end up in the same place */
		*(.bss)
	}

	kernel_virtual_end = .;
	kernel_physical_end = . - 0xC0000000;
}
