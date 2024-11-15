#include "gdt.h"
#include "multiboot.h"
#include "printk.h"
#include "vga.h"

void kernel_main(multiboot_t *multiboot) {
    (void)multiboot;

    vga_install();
    gdt_install();

    multiboot_uint32_t mmap_length = multiboot->mmap_length;
    multiboot_uint32_t mmap_addr = multiboot->mmap_addr;

    printk("Memory map address: 0x%08x\n", mmap_addr);
    printk("Memory map length: 0x%08x\n", mmap_length);

    mmap_entry_t *entry = (mmap_entry_t *)multiboot->mmap_addr;

    while (entry < (mmap_entry_t *)(multiboot->mmap_addr + multiboot->mmap_length)) {
        entry = (mmap_entry_t *)((unsigned int)entry + entry->size + sizeof(entry->size));
        if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
            printk("Available memory");
        } else if (entry->type == MULTIBOOT_MEMORY_RESERVED) {
            printk("Reserved memory");
        } else if (entry->type == MULTIBOOT_MEMORY_ACPI_RECLAIMABLE) {
            printk("ACPI reclaimable memory");
        } else if (entry->type == MULTIBOOT_MEMORY_NVS) {
            printk("NVS memory");
        } else if (entry->type == MULTIBOOT_MEMORY_BADRAM) {
            printk("Bad memory");
        } else {
            printk("Unknown memory");
        }
        printk(" (start: 0x%08x,", entry->addr);
        printk(" end: 0x%08x)\n", entry->addr + entry->len);
    }

    printk("Hello! %s!\n", "ExampleOS");
    while (1) __asm__("hlt");
}
