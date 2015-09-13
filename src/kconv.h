#ifndef KERNEL_KCONV_H
#define KERNEL_KCONV_H

#include "typedef.h"

int strlen (const char *);
char *strrchr (const char *, char);
char *strlchr (const char *, char);
int strindx (const char *, char);
char *strcpy (char *, const char *);
char *strncpy (char *, const char *, size_t);
int strncmp (const char *, const char *, size_t);
int strcmp (const char *, const char *);
char *strcat (char *, const char *);
char *strncat (char *, const char *, size_t);
void reverse (char *);
void itoa (char *, int);
void itox (char *, unsigned int);
int atoi (char *);
int strtol (char *, int);

#endif