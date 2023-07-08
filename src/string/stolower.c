#include <ctype.h>

void stolower(char *s)
{
    for(; *s; s++)
        *s=tolower(*s);
}