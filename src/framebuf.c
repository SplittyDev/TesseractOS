#include "typedef.h"
#include "framebuf.h"
#include "portio.h"
#include "memio.h"

uint8_t x;
uint8_t y;
uint8_t foreground;
uint8_t background;
uintptr_t *ptr;

void framebuf_init (void) {
    x = 0;
    y = 0;
    foreground = COLOR_WHITE;
    background = COLOR_BLACK;
    ptr = (uintptr_t *)FRAMEBUF_ADDR;
}

void set_background_color (uint8_t color) {
    background = color;
}

void set_foreground_color (uint8_t color) {
    foreground = color;
}

void set_color (uint8_t bg, uint8_t fg) {
    background = bg;
    foreground = fg;
}

void reset_color () {
    background = COLOR_BLACK;
    foreground = COLOR_WHITE;
}

void putc_internal (const uint8_t chr, bool_t singleop) {
    switch (chr) {
        case KEY_BACKSPACE:
            if (x > 0)
                x--;
            break;
        case KEY_TAB:
            x = (x + 8) & ~(8 - 1);
            break;
        case KEY_CARRIAGE_RETURN:
            x = 0;
            break;
        case KEY_NEWLINE:
            x = 0;
            y++;
            break;
        default:
            ptr[where ()] = makeattrib (chr);
            x++;
            break;
    }

    checkoverflow ();
    scroll ();

    if (singleop)
        cursor ();
}

void putc (const uint8_t chr) {
    putc_internal (chr, true);
}

void puts (const char *str) {
    size_t i = 0;
    while (str[i] != KEY_TERMINATE)
        putc_internal (str[i++], false);
    cursor ();
}

void scroll (void) {
    if (y >= TERMINAL_HEIGHT) {
        uint8_t tmp  = y - TERMINAL_HEIGHT + 1;
        uint8_t tmp2 = (TERMINAL_HEIGHT - tmp) * TERMINAL_WIDTH;
        memcpy ((void *)ptr, (void *)(ptr + tmp * TERMINAL_WIDTH), tmp2 * 2);
        memset ((void *)(ptr + tmp2), makeattrib (KEY_BLANK), TERMINAL_WIDTH);
        y = TERMINAL_HEIGHT - 1;
    }
}

void clear (void) {
    size_t i = 0;
    for (; i < TERMINAL_HEIGHT; i++)
        memset ((void *)(ptr + i * TERMINAL_WIDTH), KEY_BLANK, TERMINAL_WIDTH);
    x = 0;
    y = 0;
    cursor ();
}

void cursor (void) {
    outb (0x3D4, 14);
    outb (0x3D5, where () >> 8);
    outb (0x3D4, 15);
    outb (0x3D5, where ());
}

void checkoverflow (void) {
    if (x > TERMINAL_WIDTH) {
        x = 0;
        y++;
    }
}

size_t where (void) {
    return y * TERMINAL_WIDTH + x;
}

uint16_t makecolor (void) {
    return foreground | (background << 4);
}

uint16_t makeattrib (uint8_t chr) {
    return chr | (makecolor () << 8);
}