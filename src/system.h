#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

#include "typedef.h"

#define STI asm volatile ("sti")
#define CLI asm volatile ("cli")
#define HLT asm volatile ("hlt")

typedef struct stackframe {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t intr, error;
    uint32_t eip, cs, eflags, useresp, ss;
} stackframe_t;

#endif