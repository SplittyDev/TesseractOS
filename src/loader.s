section multiboot

MB_MAGIC    equ 0x1BADB002
MB_ALIGN    equ 1 << 0
MB_MEMINFO  equ 1 << 1
MB_GRAPHICS equ 1 << 2
MB_FLAGS    equ MB_ALIGN | MB_MEMINFO
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

section .text
global _start
extern kmain
_start:
    mov esp, stack_top
    call kmain

_stop:
    cli
    hlt
    jmp _stop

global gdt_flush
gdt_flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x8:gdt_flush_cs
    ret

gdt_flush_cs:
    ret

extern idt_handle_general
handle_common_intr:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call idt_handle_general
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 0x8
    iret

%macro isr_handle_noerr 1
global handle_intr_%1
handle_intr_%1:
    push dword 0
    push dword %1
    jmp handle_common_intr
%endmacro

%macro isr_handle 1
global handle_intr_%1
handle_intr_%1:
    push dword %1
    jmp handle_common_intr
%endmacro

isr_handle_noerr    0
isr_handle_noerr    1
isr_handle_noerr    2
isr_handle_noerr    3
isr_handle_noerr    4
isr_handle_noerr    5
isr_handle_noerr    6
isr_handle_noerr    7
isr_handle          8
isr_handle_noerr    9
isr_handle          10
isr_handle          11
isr_handle          12
isr_handle          13
isr_handle          14
isr_handle_noerr    15
isr_handle_noerr    16
isr_handle_noerr    17
isr_handle_noerr    18
isr_handle_noerr    19
isr_handle_noerr    20
isr_handle_noerr    21
isr_handle_noerr    22
isr_handle_noerr    23
isr_handle_noerr    24
isr_handle_noerr    25
isr_handle_noerr    26
isr_handle_noerr    27
isr_handle_noerr    28
isr_handle_noerr    29
isr_handle_noerr    30
isr_handle_noerr    31

isr_handle_noerr    32 ; IRQ 0
isr_handle_noerr    33 ; IRQ 1
isr_handle_noerr    34 ; IRQ 2
isr_handle_noerr    35 ; IRQ 3
isr_handle_noerr    36 ; IRQ 4
isr_handle_noerr    37 ; IRQ 5
isr_handle_noerr    38 ; IRQ 6
isr_handle_noerr    39 ; IRQ 7
isr_handle_noerr    40 ; IRQ 8
isr_handle_noerr    41 ; IRQ 9
isr_handle_noerr    42 ; IRQ 10
isr_handle_noerr    43 ; IRQ 11
isr_handle_noerr    44 ; IRQ 12
isr_handle_noerr    45 ; IRQ 13
isr_handle_noerr    46 ; IRQ 14
isr_handle_noerr    47 ; IRQ 15

section .bss
align 4
resb 8192
stack_top: