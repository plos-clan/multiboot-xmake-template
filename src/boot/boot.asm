section .multiboot

; Text Mode
dd 0x1badb002 ; MAGIC 文件魔术头, 内核识别码
dd 3          ; FLAGS
dd -464367621 ; -(MAGIC + FLAGS) 校验和

; VBE Video Mode
; dd 0x1badb002 ; 文件魔术头, 内核识别码
; dd 7          ; FLAGS
; dd -464367625 ; -(MAGIC + FLAGS)
; dd 0          ; HEADER_ADDR
; dd 0          ; LOAD_ADDR
; dd 0          ; LOAD_END_ADDR
; dd 0          ; BSS_END_ADDR
; dd 0          ; ENTRY_ADDR
; dd 0          ; MODE_TYPE
; dd 1280       ; WIDTH
; dd 768        ; HEIGHT
; dd 32         ; DEPTH
; times 52 db 0 ; 显式初始化 52 个字节为零

section .bss
align 16
stack_bottom:
resb 16384 ; 内核栈大小 16KB
stack_top:

section .text
global _start

_start:
    ; 为了设置堆栈，我们将esp寄存器指向堆栈的顶部
    mov esp, stack_top

    extern kernel_main ; 内核主函数 main.c
    call kernel_main

	; 如果内核没有更多的事情要做，将电脑置于无限循环中
    cli
L1:
    hlt
    jmp L1
