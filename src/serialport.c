#include "serialport.h"
#include "portio.h"
#include "framebuf.h"

void serial_init (uint16_t com) {
    outb (SERIAL_IER (com), 0x00);
    outb (SERIAL_LINE (com), SERIAL_LINE_ENABLE_DLAB);
    outb (SERIAL_DATA (com), 0x03);
    outb (SERIAL_IER (com), 0x00);
    outb (SERIAL_LINE (com), 0x03);
    outb (SERIAL_FIFO (com), 0xC7);
    outb (SERIAL_MODEM (com), 0x0B);
}

void serial_set_baud_rate (uint16_t com, uint32_t divisor) {
    outb (SERIAL_LINE (com), SERIAL_LINE_ENABLE_DLAB);
    outb (SERIAL_DATA (com), (divisor >> 8) & 0x00FF); // Higher 8 bits
    outb (SERIAL_DATA (com), divisor & 0x00FF); // Lower 8 bits
}

void serial_set_line (uint16_t com) {
    outb (SERIAL_LINE (com), 0x03);
}

void serial_enable_buffer (uint16_t com) {
    outb (SERIAL_FIFO (com), 0xC7);
}

bool_t serial_is_buffer_empty (uint16_t com) {
    return inb (SERIAL_LINE_STATUS (com)) & 0x20;
}

void serial_putc (uint16_t com, uint8_t chr) {
    while (!serial_is_buffer_empty (com));
    outb (com, chr);
}

void serial_puts (uint16_t com, const char *str) {
    size_t i = 0;
    while (str[i] != KEY_TERMINATE)
        serial_putc (com, str[i++]);
}

bool_t serial_buffer_contains_data (uint16_t com) {
    return inb (SERIAL_LINE_STATUS (com)) & 1;
}

char serial_readc (uint16_t com) {
    while (!serial_buffer_contains_data (com));
    return inb (com);
}