ENTRY(_start)

SECTIONS
{

	. = 2M;

	.multiboot : {
		*(.multiboot)
	}

	.text : {
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