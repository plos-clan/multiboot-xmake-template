.section .multiboot

# Text Mode
.long 0x1badb002 # MAGIC 文件魔术头, 内核识别码
.long 3          # FLAGS
.long -(0x1badb002 + 3) # -(MAGIC + FLAGS) 校验和

# VBE Video Mode
# .long 0x1badb002 # 文件魔术头, 内核识别码
# .long 7          # FLAGS
# .long -(0x1badb002 + 7) # -(MAGIC + FLAGS) 校验和
# .long 0          # HEADER_ADDR
# .long 0          # LOAD_ADDR
# .long 0          # LOAD_END_ADDR
# .long 0          # BSS_END_ADDR
# .long 0          # ENTRY_ADDR
# .long 0          # MODE_TYPE
# .long 1280       # WIDTH
# .long 768        # HEIGHT
# .long 32         # DEPTH
# .fill 52, 1, 0   # 显式初始化 52 个字节为零

.section .bss
.balign 16
stack_bottom:
.space 16384 # 内核栈大小 16KB
stack_top:

.section .text
.global _start
_start:
    # 为了设置堆栈，我们将esp寄存器指向堆栈的顶部
    movl $stack_top, %esp

    # 传递 multiboot 信息到 C 代码
    push %ebx

    .extern kernel_main # 内核主函数 main.c
    call kernel_main

    # 如果内核没有更多的事情要做，将电脑置于无限循环中
    cli
1:
    hlt
    jmp 1b
