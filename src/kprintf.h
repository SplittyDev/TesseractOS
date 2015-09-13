#ifndef KERNEL_KPRINTF_H
#define KERNEL_KPRINTF_H

#include "karg.h"

void kvsprintf (char *, const char *, va_list);
char *ksprintf (char[], const char *, ...);
void kprintf (const char *, ...);

#endif