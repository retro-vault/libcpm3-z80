/*
 * stoupper.c
 *
 * stoupper function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <ctype.h>

void stoupper(char *s)
{
    for(; *s; s++)
        *s=toupper(*s);
}