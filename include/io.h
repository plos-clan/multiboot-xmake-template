#pragma once

#include "klibc.h"

void io_hlt(void);
void io_cli(void);
void io_sti(void);
void io_stihlt(void);
uint8_t io_in8(uint16_t port);
uint16_t io_in16(uint16_t port);
uint32_t io_in32(uint16_t port);
void io_out8(uint16_t port, uint8_t value);
void io_out16(uint16_t port, uint16_t value);
void io_out32(uint16_t port, uint32_t value);

void io_hlt(void) {
    __asm__ __volatile__("hlt");
}

void io_cli(void) {
    __asm__ __volatile__("cli");
}

void io_sti(void) {
    __asm__ __volatile__("sti");
}

void io_stihlt(void) {
    __asm__ __volatile__("sti; hlt");
}

uint8_t io_in8(uint16_t port) {
    uint8_t result;
    __asm__ __volatile__("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

uint16_t io_in16(uint16_t port) {
    uint16_t result;
    __asm__ __volatile__("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

uint32_t io_in32(uint16_t port) {
    uint32_t result;
    __asm__ __volatile__("inl %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void io_out8(uint16_t port, uint8_t value) {
    __asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
}

void io_out16(uint16_t port, uint16_t value) {
    __asm__ __volatile__("outw %0, %1" : : "a"(value), "Nd"(port));
}

void io_out32(uint16_t port, uint32_t value) {
    __asm__ __volatile__("outl %0, %1" : : "a"(value), "Nd"(port));
}
