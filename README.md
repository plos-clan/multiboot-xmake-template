# Multiboot C xmake Template

This repository contains a basic x86 kernel in C using Multiboot.

## About

The template source code is borrowed from "CP_Kernel".
Tested by x86 physical machine platform, there are no obvious bugs.

[**ProjectStruct**](docs/ProjectStruct.md) has some project struct info.

## Dependencies

* `xmake` `xorriso`

> When first running `xmake`, it will download zig as cross-compiler.

> If you choose to use the GRUB bootloader, you will need to install `grub-pc-bin`

## Xmake targets

Running `xmake` will build the kernel and create a bootable ISO image.

Running `xmake run` will build above automatically and run it in QEMU.

## How to enable vbe video mode

Open `src/boot/boot.asm`, comment out `Text Mode` section and uncomment `VBE Video Mode` section.

> VBE Graphics memory address: `multiboot->framebuffer_addr` \
> Video width `multiboot->framebuffer_width` \
> Video height `multiboot->framebuffer_height`

## About GRUB Bootloader

1. Create file `assets/boot/grub/grub.cfg`

```c
set timeout=60
set default=0

menuentry "ExampleOS" {
    multiboot /kernel.elf
    boot
}
```

2. You'll need to comment out the "Limine Build ISO" section in `xmake.lua`
3. and uncomment the "GRUB Build ISO" section in `xmake.lua`
