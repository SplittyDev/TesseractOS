#ifndef KERNEL_SERIALPORT_H
#define KERNEL_SERIALPORT_H

#include "typedef.h"

#define COM1_BASE                   0x3F8
#define COM2_BASE                   0x2F8
#define COM3_BASE                   0x3E8
#define COM4_BASE                   0x2E8

#define SERIAL_DATA(base)           (base)
#define SERIAL_IER(base)            (base + 1)
#define SERIAL_FIFO(base)           (base + 2)
#define SERIAL_LINE(base)           (base + 3)
#define SERIAL_MODEM(base)          (base + 4)
#define SERIAL_LINE_STATUS(base)    (base + 5)

#define SERIAL_LINE_ENABLE_DLAB     0x80
#define SERIAL_DEFAULT_BAUD_RATE    0x9600

void serial_init (uint16_t com);
void serial_set_baud_rate (uint16_t com, uint32_t divisor);
void serial_set_line (uint16_t com);
void serial_enable_buffer (uint16_t com);
void serial_putc (uint16_t com, uint8_t chr);
void serial_puts (uint16_t com, const char *str);
bool_t serial_is_buffer_empty (uint16_t com);
bool_t serial_buffer_contains_data (uint16_t com);
char serial_readc (uint16_t com);

#endif