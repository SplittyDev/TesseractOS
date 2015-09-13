#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include "system.h"
#include "typedef.h"

#define IDT_ENTRIES 256

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_entry idt[IDT_ENTRIES];

void idt_init ();
void idt_install_handler (uint8_t, void (*)(stackframe_t *));
void idt_uninstall_handler (uint8_t);

void idt_load ();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void idt_handle_irq (stackframe_t *);
void idt_handle_syscall (stackframe_t *);
void idt_handle_general (stackframe_t *);
void idt_handle_exception (stackframe_t *);

static const char *exception_messages[] = {
        "DIVIDE BY ZERO EXCEPTION\n",              // 0x00
        "DEBUG EXCEPTION\n",                       // 0x01
        "NON MASKABLE INTERRUPT EXCEPTION\n",      // 0x02
        "BREAKPOINT EXCEPTION\n",                  // 0x03
        "INTO DETECTED OVERFLOW EXCEPTION\n",      // 0x04
        "OUT OF BOUNDS EXCEPTION\n",               // 0x05
        "INVALID OPCODE EXCEPTION\n",              // 0x06
        "NO COPROCESSOR EXCEPTION\n",              // 0x07
        "DOUBLE FAULT EXCEPTION\n",                // 0x08
        "COPROCESSOR SEGMENT OVERRUN EXCEPTION\n", // 0x09
        "BAD TSS EXCEPTION\n",                     // 0x0A
        "SEGMENT NOT PRESENT EXCEPTION\n",         // 0x0B
        "STACK FAULT EXCEPTION\n",                 // 0x0C
        "GENERAL PROTECTION FAULT EXCEPTION\n",    // 0x0D
        "PAGE FAULT EXCEPTION\n",                  // 0x0E
        "UNKNOWN INTERRUPT EXCEPTION\n",           // 0x0F
        "COPROCESSOR FAULT EXCEPTION\n",           // 0x10
        "ALIGNMENT CHECK EXCEPTION\n",             // 0x11
        "MACHINE CHECK EXCEPTION\n",               // 0x12
};

#endif