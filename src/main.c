#include "typedef.h"
#include "system.h"
#include "framebuf.h"
#include "serialport.h"
#include "gdt.h"
#include "idt.h"

void kmain () {
    CLI;
    framebuf_init ();
    serial_init (COM1_BASE);
    serial_puts (COM1_BASE, "Hello from TesseractOS!");
    gdt_init ();
    idt_init ();
}