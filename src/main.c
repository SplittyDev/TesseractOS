#include "typedef.h"
#include "system.h"
#include "framebuf.h"
#include "serialport.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"

void kmain () {
    CLI;
    framebuf_init ();
    serial_init (COM1_BASE);
    serial_puts (COM1_BASE, "Initializing GDT\n");
    gdt_init ();
    serial_puts (COM1_BASE, "Initializing PIC\n");
    pic_init ();
    serial_puts (COM1_BASE, "Initializing IDT\n");
    idt_init ();
    serial_puts (COM1_BASE, "Enabling interrupts\n");
    STI;
    puts ("Hello from TesseractOS!");
}