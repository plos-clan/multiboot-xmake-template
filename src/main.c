#include "gdt.h"
#include "printk.h"
#include "multiboot.h"
#include "vga.h"

void kernel_main(multiboot_t *multiboot) {
    vga_install();
    gdt_install();

    printk("Hello! %s!\n", "ExampleOS");
    while (1) __asm__("hlt");
}