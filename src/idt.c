#include "idt.h"
#include "isr.h"
#include "system.h"
#include "typedef.h"
#include "memio.h"
#include "portio.h"
#include "serialport.h"
#include "framebuf.h"
#include "kprintf.h"

struct {
	uint16_t	limit;
	void 		*pointer;
} __attribute__((packed)) idt_ptr = {
		.limit		= (sizeof (struct idt_entry) * 256) - 1,
		.pointer	= &idt
};

void idt_init () {

	// Clear IDT
	memset ((void *)&idt, 0, sizeof(struct idt_entry) * 256);

	// Exceptions
	idt_set_gate (0x00, (unsigned) handle_intr_0,  0x08, 0x8E);
	idt_set_gate (0x01, (unsigned) handle_intr_1,  0x08, 0x8E);
	idt_set_gate (0x02, (unsigned) handle_intr_2,  0x08, 0x8E);
	idt_set_gate (0x03, (unsigned) handle_intr_3,  0x08, 0x8E);
	idt_set_gate (0x04, (unsigned) handle_intr_4,  0x08, 0x8E);
	idt_set_gate (0x05, (unsigned) handle_intr_5,  0x08, 0x8E);
	idt_set_gate (0x06, (unsigned) handle_intr_6,  0x08, 0x8E);
	idt_set_gate (0x07, (unsigned) handle_intr_7,  0x08, 0x8E);
	idt_set_gate (0x08, (unsigned) handle_intr_8,  0x08, 0x8E);
	idt_set_gate (0x09, (unsigned) handle_intr_9,  0x08, 0x8E);
	idt_set_gate (0x0A, (unsigned) handle_intr_10, 0x08, 0x8E);
	idt_set_gate (0x0B, (unsigned) handle_intr_11, 0x08, 0x8E);
	idt_set_gate (0x0C, (unsigned) handle_intr_12, 0x08, 0x8E);
	idt_set_gate (0x0D, (unsigned) handle_intr_13, 0x08, 0x8E);
	idt_set_gate (0x0E, (unsigned) handle_intr_14, 0x08, 0x8E);
	idt_set_gate (0x0F, (unsigned) handle_intr_15, 0x08, 0x8E);
	idt_set_gate (0x10, (unsigned) handle_intr_16, 0x08, 0x8E);
	idt_set_gate (0x11, (unsigned) handle_intr_17, 0x08, 0x8E);
	idt_set_gate (0x12, (unsigned) handle_intr_18, 0x08, 0x8E);
	idt_set_gate (0x13, (unsigned) handle_intr_19, 0x08, 0x8E);
	idt_set_gate (0x14, (unsigned) handle_intr_20, 0x08, 0x8E);
	idt_set_gate (0x15, (unsigned) handle_intr_21, 0x08, 0x8E);
	idt_set_gate (0x16, (unsigned) handle_intr_22, 0x08, 0x8E);
	idt_set_gate (0x17, (unsigned) handle_intr_23, 0x08, 0x8E);
	idt_set_gate (0x18, (unsigned) handle_intr_24, 0x08, 0x8E);
	idt_set_gate (0x19, (unsigned) handle_intr_25, 0x08, 0x8E);
	idt_set_gate (0x1A, (unsigned) handle_intr_26, 0x08, 0x8E);
	idt_set_gate (0x1B, (unsigned) handle_intr_27, 0x08, 0x8E);
	idt_set_gate (0x1C, (unsigned) handle_intr_28, 0x08, 0x8E);
	idt_set_gate (0x1D, (unsigned) handle_intr_29, 0x08, 0x8E);
	idt_set_gate (0x1E, (unsigned) handle_intr_30, 0x08, 0x8E);
	idt_set_gate (0x1F, (unsigned) handle_intr_31, 0x08, 0x8E);

	// IRQs
	idt_set_gate (0x20, (unsigned) handle_intr_32, 0x08, 0x8E);
	idt_set_gate (0x21, (unsigned) handle_intr_33, 0x08, 0x8E);
	idt_set_gate (0x22, (unsigned) handle_intr_34, 0x08, 0x8E);
	idt_set_gate (0x23, (unsigned) handle_intr_35, 0x08, 0x8E);
	idt_set_gate (0x24, (unsigned) handle_intr_36, 0x08, 0x8E);
	idt_set_gate (0x25, (unsigned) handle_intr_37, 0x08, 0x8E);
	idt_set_gate (0x26, (unsigned) handle_intr_38, 0x08, 0x8E);
	idt_set_gate (0x27, (unsigned) handle_intr_39, 0x08, 0x8E);
	idt_set_gate (0x28, (unsigned) handle_intr_40, 0x08, 0x8E);
	idt_set_gate (0x29, (unsigned) handle_intr_41, 0x08, 0x8E);
	idt_set_gate (0x2A, (unsigned) handle_intr_42, 0x08, 0x8E);
	idt_set_gate (0x2B, (unsigned) handle_intr_43, 0x08, 0x8E);
	idt_set_gate (0x2C, (unsigned) handle_intr_44, 0x08, 0x8E);
	idt_set_gate (0x2D, (unsigned) handle_intr_45, 0x08, 0x8E);
	idt_set_gate (0x2E, (unsigned) handle_intr_46, 0x08, 0x8E);
	idt_set_gate (0x2F, (unsigned) handle_intr_47, 0x08, 0x8E);

	// Load IDT
	idt_load ();
}

void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt[num].base_lo  = base         & 0xFFFF;
	idt[num].base_hi  = (base >> 16) & 0xFFFF;
	idt[num].sel      = sel;
	idt[num].zero     = 0;
	idt[num].flags    = flags;
}

void idt_load () {
	asm volatile ("lidt %0" : : "m" (idt_ptr));
}

void *irq_handlers[16] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
};

void idt_install_handler (uint8_t irq, void (*handler)(stackframe_t *frame)) {
	irq_handlers[irq] = handler;
	serial_puts (COM1_BASE, "Installed IRQ handler\n");
}

void idt_uninstall_handler (uint8_t irq) {
	irq_handlers[irq] = 0;
}

void idt_handle_exception (stackframe_t *frame) {
	// Print exception message
	kprintf ("\nEXCEPTION: %s\n", exception_messages[frame->intr]);
	puts ("[CPU state]\n");
	kprintf ("GS     : %x\n",  frame->gs);
	kprintf ("FS     : %x\n",  frame->fs);
	kprintf ("ES     : %x\n",  frame->es);
	kprintf ("DS     : %x\n",  frame->ds);
	kprintf ("EDI    : %x\n",  frame->edi);
	kprintf ("ESI    : %x\n",  frame->esi);
	kprintf ("EBP    : %x\n",  frame->ebp);
	kprintf ("ESP    : %x\n",  frame->esp);
	kprintf ("EBX    : %x\n",  frame->ebx);
	kprintf ("EDX    : %x\n",  frame->edx);
	kprintf ("ECX    : %x\n",  frame->ecx);
	kprintf ("EAX    : %x\n",  frame->eax);
	kprintf ("EIP    : %x\n",  frame->eip);
	kprintf ("CS     : %x\n",  frame->cs);
	kprintf ("SS     : %x\n",  frame->ss);
	kprintf ("EFLAGS : %x\n",  frame->eflags);
	kprintf ("USERESP: %x\n",  frame->useresp);

	// Halt
	while (true) {
		CLI;
		HLT;
	}
}

void idt_handle_irq (stackframe_t *frame) {

	// Blank IRQ handler
	void (*handler)(stackframe_t *frame);

	// Set our handler to the actual IRQ handler
	handler = irq_handlers[frame->intr - 32];

	// Call the handler
	if (handler)
		handler (frame);
}

void idt_handle_general (stackframe_t *frame) {
	// Exceptions
	if (frame->intr <= 0x1F) {

		// Call exception handler
		idt_handle_exception (frame);
	}

	// IRQs
	if (frame->intr >= 0x20 && frame->intr <= 0x2F) {

		// Call IRQ handler
		idt_handle_irq (frame);

		// Send EOI to slave interrupt controller
		if (frame->intr >= 0x28) {
			outb (0xA0, 0x20);
		}

		// Send EOI to master interrupt controller
		outb (0x20, 0x20);
	}
}