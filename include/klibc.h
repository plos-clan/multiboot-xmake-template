#pragma once

#include "types/stdarg.h"
#include "types/stdbool.h"
#include "types/stddef.h"
#include "types/stdint.h"

#define isdigit(c) ((c) >= '0' && (c) <= '9')

// string.h
void *memset(void *s, int c, size_t n);
void *memcpy(void *dst, const void *in, size_t n);
void *memmove(void *dst, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t maxlen);
char *strcat(char *dst, const char *src);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

// stdio.h
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
