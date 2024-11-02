# Multiboot C xmake Template

This repository contains a basic x86 kernel in C using Multiboot.

## Dependencies

* `xmake` `xorriso` `nasm`

> If you choose to use the GRUB bootloader, you will need to install `grub-pc-bin`

## Xmake targets

Running `xmake` will build the kernel and create a bootable ISO image.

Running `xmake run` will build above automatically and run it in QEMU.

## Directory structure

* `src` Your kernel source code directory.
* `include` Your kernel header files directory.
* `assets` Will be used as the root directory of the ISO image. Put your assets here.

## How to enable vbe video mode

Open `src/boot/boot.asm`, comment out `Text Mode` section and uncomment `VBE Video Mode` section.

> VBE Graphics memory address: `multiboot->framebuffer_addr` \
> Video width `multiboot->framebuffer_width` \
> Video height `multiboot->framebuffer_height`

## About GRUB Bootloader

1. Create file `iso/boot/grub/grub.cfg`

``` cfg
set timeout=60
set default=0

menuentry "ExampleOS" {
    multiboot /kernel.elf
    boot
}
```

2. You'll need to comment out the "Limine Build ISO" section in `xmake.lua`
3. and uncomment the "GRUB Build ISO" section in `xmake.lua`
