#ifndef KERNEL_MEMIO_H
#define KERNEL_MEMIO_H

#include "typedef.h"

static inline void *memcpy (void *dest, void *src, size_t size) {
    asm volatile ("cld");
    asm volatile ("rep movsb" : "+c" (size), "+S" (src), "+D" (dest) :: "memory");
    return (void *)0;
}

static inline void *memset (void *b, int val, size_t size) {
    asm volatile ("cld");
    asm volatile ("rep stosb" : "+c" (size), "+D" (b) : "a" (val) : "memory");
    return b;
}

static inline uintptr_t *memsetw (uintptr_t *ptr, uint8_t val, size_t size) {
    int i = 0;
    for (; i < size; ++i) {
        ptr[i] = val;
    }
    return ptr;
}

#endif