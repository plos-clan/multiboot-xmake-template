#include "kprintf.h"
#include "krlibc.h"

extern void vga_writestring(const char *data);

void printk(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char *buf[1024] = {0};
    vsprintf(buf, format, ap);
    k_print(buf);
    va_end(ap);
}

void k_print(const char* message){
    vga_writestring(message);
}
