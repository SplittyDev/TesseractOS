#ifndef KERNEL_TYPEDEF_H
#define KERNEL_TYPEDEF_H

#define NULL                (void *)0

#define true                1
#define false               0

typedef char                int8_t;
typedef short               int16_t;
typedef long                int32_t;
typedef long long           int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned long       uint32_t;
typedef unsigned long long  uint64_t;

typedef unsigned char       bool_t;
typedef unsigned short      size_t;
typedef unsigned short      port_t;
typedef unsigned short      uintptr_t;
typedef unsigned long       uintlongptr_t;

#endif