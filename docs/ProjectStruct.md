# Project Struct

<hr>


* `src` Your kernel source code directory.
* `include` Your kernel header files directory.
* `assets` Will be used as the root directory of the ISO image. Put your assets here.


## src

* `main.c` Kernel init.
* `gdt.c` Config global description table and task status segment.

### boot

* `asmfunc.asm` Assembler function.
* `boot.asm` multiboot flags and init kernel stack.
* `io.asm` all I/O assembler function.

### driver

* `vga.c` VGA video driver.

### util

* `kprintf.c` printk implement
* `krlibc.c` Kernel libc implement
