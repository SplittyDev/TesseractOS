#include "typedef.h"
#include "framebuf.h"
#include "serialport.h"

void kmain () {
    framebuf_init ();
    serial_init (COM1_BASE);
    serial_puts (COM1_BASE, "Hello from TesseractOS!");
}