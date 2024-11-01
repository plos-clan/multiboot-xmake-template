# Multiboot C xmake Template

This repository contains a basic x86 kernel in C using Multiboot.

## Dependencies

* `xmake` `xorriso` `mtools` `zig` `nasm`

> Use GRUB Bootloader, you need install `grub-pc-bin`

# Struct

* `src` Your kernel source code directory.
* `iso` ISO image directory.

# How to enable vbe video model

1. delete `src/boot/boot.asm`
2. rename `src/boot/boot_vbe.asm.disable` to `src/boot/boot.asm`

> VBE Graphics memory address: `multiboot->framebuffer_addr` \
> Video width `multiboot->framebuffer_width` \
> Video height `multiboot->framebuffer_height`

# About GRUB Bootloader

1. create file `iso/boot/grub/grub.cfg`

``` cfg
set timeout=60
set default=0

menuentry "ExampleOS" {
    multiboot /kernel.elf
    boot
}
```
2. You'll need to comment out the "Limine Build ISO" section in xmake.lua
3. and uncomment the "GRUB Build ISO" section in xmake.lua
