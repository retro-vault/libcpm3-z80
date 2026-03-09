/*
 * puts.c
 *
 * Write a string to standard output and append a newline.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int puts(const char *s)
{
   int i = 0;
   while(s[i]) { putchar(s[i]); i++; }
   putchar('\n');
   return i + 1;
}
