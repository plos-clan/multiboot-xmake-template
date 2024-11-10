#include "klibc.h"

size_t strlen(const char *s) {
    size_t len = 0;
    for (; s[len] != '\0'; len++)
        ;
    return len;
}

size_t strnlen(const char *s, size_t maxlen) {
    const char *es = s;
    while (*es && maxlen) {
        es++;
        maxlen--;
    }
    return (es - s);
}

char *strcpy(char *dst, const char *src) {
    char *ret = dst;
    while ((*dst++ = *src++) != '\0');
    return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
    char *ret = dst;
    while (n-- && (*dst++ = *src++) != '\0');
    return ret;
}

char *strcat(char *dst, const char *src) {
    char *ret = dst;
    while (*dst) dst++;
    while ((*dst++ = *src++) != '\0');
    return ret;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) s1++, s2++;
    return (size_t)*s1 - (size_t)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n-- && *s1 && *s1 == *s2) s1++, s2++;
    return n == (size_t)-1 ? 0 : (size_t)*s1 - (size_t)*s2;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;
    void *ret = s;
    while (n--) *p++ = (uint8_t)c;
    return ret;
}

void *memmove(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dst, *s = (uint8_t *)src;
    if (d < s) {
        while (n--) *d++ = *s++;
    } else {
        d += n, s += n;
        while (n--) *--d = *--s;
    }
    return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    void *ret = dst;
    while (n--) *d++ = *s++;
    return ret;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    uint8_t *p1 = (uint8_t *)s1, *p2 = (uint8_t *)s2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] - p2[i];
    }
    return 0;
}
