/*
 * tmpfile.c
 *
 * Create and open a temporary stream for read-write access.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

char *tmpnam(char *s);

FILE *tmpfile(void)
{
    char name[16];
    if (tmpnam(name) == NULL)
        return NULL;
    return fopen(name, "w+");
}
