#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

void pic_init ();
void pic_remap_master ();
void pic_remap_slave ();
void pic_unmask ();

#endif