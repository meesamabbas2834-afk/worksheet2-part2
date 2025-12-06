global loader
extern kmain

MB_HEADER_MAGIC  equ 0x1BADB002
MB_HEADER_FLAGS  equ 0x0
MB_HEADER_CHECK  equ -MB_HEADER_MAGIC

section .text
align 4
    dd MB_HEADER_MAGIC
    dd MB_HEADER_FLAGS
    dd MB_HEADER_CHECK

loader:
    mov esp, sys_stack + STACK_BYTES
    call kmain

freeze_cpu:
    jmp freeze_cpu

section .bss
align 4
STACK_BYTES equ 4096
sys_stack:
    resb STACK_BYTES
