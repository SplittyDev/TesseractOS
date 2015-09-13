global loader
global gdt_flush

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
    cli
    mov esp, kernel_stack + SZ_STACK
    call kmain

.loop:
    jmp .loop

gdt_flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:gdt_flush_cs

gdt_flush_cs:
    ret

section .bss
align 4
kernel_stack:
    resb SZ_STACK