#include "multiboot.h"
#include "ctypes.h"

extern void vga_writestring(const char *data);
extern void vga_install(void);

_Noreturn void kernel_main(multiboot_t *multiboot){
    vga_install();

    vga_writestring("Hello! ExampleOS!\n");

    while(1) __asm__("hlt");
}