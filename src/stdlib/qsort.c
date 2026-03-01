/*
 * qsort.c
 *
 * qsort function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void _swap(void *v1, void *v2, size_t size)
{
    unsigned char *a = (unsigned char *)v1;
    unsigned char *b = (unsigned char *)v2;
    while (size--) {
        unsigned char t = *a;
        *a++ = *b;
        *b++ = t;
    }
}

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    static unsigned gap, byte_gap, i;
    static char *p;
    for (gap = nitems >> 1; gap > 0; gap >>= 1)
    {
        byte_gap = gap * size;
        for (i = gap; i < nitems; ++i)
            for (p = base + i * size - byte_gap; p >= base; p -= byte_gap)
            {
                if ((*compar)(p, p + byte_gap) <= 0)
                    break;
                _swap(p, p + byte_gap, size);
            }
    }
}
