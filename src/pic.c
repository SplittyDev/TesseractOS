#include "pic.h"
#include "portio.h"

void pic_init () {
    pic_remap_master ();
    pic_remap_slave ();
    pic_unmask ();
}

void pic_remap_master () {
    outb (0x20, 0x11);
    outb (0x21, 0x20);
    outb (0x21, 0x04);
    outb (0x21, 0x01);
}

void pic_remap_slave () {
    outb (0xA0, 0x11);
    outb (0xA1, 0x28);
    outb (0xA1, 0x02);
    outb (0xA1, 0x01);
}

void pic_unmask () {
    outb (0x21, 0x0);
    outb (0xA1, 0x0);
}