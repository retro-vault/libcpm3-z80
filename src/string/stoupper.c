/*
 * stoupper.c
 *
 * Convert all characters of a string to uppercase in place.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

void stoupper(char *s)
{
    for(; *s; s++)
        *s=toupper(*s);
}
