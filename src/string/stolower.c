/*
 * stolower.c
 *
 * stolower function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <ctype.h>

void stolower(char *s)
{
    for(; *s; s++)
        *s=tolower(*s);
}