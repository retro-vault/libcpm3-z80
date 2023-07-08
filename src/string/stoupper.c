#include <ctype.h>

void stoupper(char *s)
{
    for(; *s; s++)
        *s=toupper(*s);
}