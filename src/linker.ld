OUTPUT_FORMAT(elf32-i386)

ENTRY(_start)

SECTIONS
{
	. = 2M;

	.text : {
  		KEEP(*(.multiboot))
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
	}

	.bss : {
		*(COMMON)
		*(.bss)
	}
}