/*
 * bsearch.c
 *
 * Search a sorted array for a key using binary search.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nitems, size_t size,
    int (*compar)(const void *, const void *))
{
    const char *p = (const char *)base;
    size_t lo = 0;
    size_t hi = nitems;

    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        const void *elem = p + mid * size;
        int cmp = compar(key, elem);
        if (cmp == 0)
            return (void *)elem;
        if (cmp < 0)
            hi = mid;
        else
            lo = mid + 1;
    }

    return NULL;
}
