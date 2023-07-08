/*
 * puts.c
 *
 * puts function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int puts(const char *s)
{
   int i = 0;
   while(s[i]) { putchar(s[i]); i++; }
   return 1;
}