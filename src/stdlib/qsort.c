#include <stdlib/_stdlib.h>

#define MAX_EL_LEN 8
void _swap(void *v1, void *v2, size_t size)
{
    char temp[MAX_EL_LEN];
    memcpy(temp, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, temp, size);
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