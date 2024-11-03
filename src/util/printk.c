#include "printk.h"
#include "klibc.h"
#include "vga.h"

void printk(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buf[1024] = {0};
    vsprintf(buf, format, ap);
    vga_writestring(buf);
    va_end(ap);
}
