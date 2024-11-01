ENTRY(_start)

SECTIONS
{

	. = 2M;

	.multiboot :
	{
		*(.multiboot)
	}

	.text :
	{
    	text = .; _text = .; __text = .;
		*(.text)
	}

	.rodata ALIGN(0x1000):
	{
		*(.rodata)
	}

	.data ALIGN(0x1000):
	{
    	data = .; _data = .; __data = .;
		*(.data)
	}

	.bss :
	{
    	bss = .; _bss = .; __bss = .;
		*(COMMON)
		*(.bss)
	}
}