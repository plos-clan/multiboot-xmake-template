#include "multiboot.h"
#include "ctypes.h"
#include "description_table.h"
#include "kprintf.h"

extern void vga_install(void);

_Noreturn void kernel_main(multiboot_t *multiboot){
    vga_install();

    gdt_install();
    printk("Hello! %s!\n","ExampleOS");

    while(1) __asm__("hlt");
}