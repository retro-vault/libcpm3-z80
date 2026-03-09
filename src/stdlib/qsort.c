/*
 * qsort.c
 *
 * Sort an array in place using a Shell-sort and a comparator callback.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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

void qsort(void *base, size_t nitems, size_t size,
    int (*compar)(const void *, const void *))
{
    unsigned gap, byte_gap, i;
    char *p;
    for (gap = nitems >> 1; gap > 0; gap >>= 1)
    {
        byte_gap = gap * size;
        for (i = gap; i < nitems; ++i)
            for (p = (char *)base + i * size - byte_gap; p >= (char *)base; p -= byte_gap)
            {
                if ((*compar)(p, p + byte_gap) <= 0)
                    break;
                _swap(p, p + byte_gap, size);
            }
    }
}
