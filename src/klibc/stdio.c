#include "klibc.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

int vsprintf(char *buf, const char *fmt, va_list args) {
    return stbsp_vsprintf(buf,fmt,args);
}
