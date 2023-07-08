/*
 * strtol.c
 *
 * strtol function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

#ifndef LEAN_AND_MEAN
long strtol(char *nptr, char **endptr, int base)
{
    long result;
    char *p = nptr;
    while (isspace(*p))
    {
        p++;
    }
    if (*p == '-')
    {
        p++;
        result = -strtoul(p, endptr, base);
    }
    else
    {
        if (*p == '+')
            p++;
        result = strtoul(p, endptr, base);
    }
    if (endptr != 0 && *endptr == p)
    {
        *endptr = nptr;
    }
    return result;
}

#endif /* LEAN_AND_MEAN */