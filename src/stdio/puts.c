#include <stdio/_stdio.h>

int puts(const char *s)
{
   int i = 0;
   while(s[i]) { putchar(s[i]); i++; }
   return 1;
}