global loader

MB_MAGIC    equ 0x1BADB002
MB_FLAGS    equ 0x0
MB_CHECKSUM equ -(MB_MAGIC)
SZ_STACK    equ 4096

section .text
align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

extern kmain
loader:
    mov esp, kernel_stack + SZ_STACK
    call kmain

.loop:
    jmp .loop

section .bss
align 4
kernel_stack:
    resb SZ_STACK