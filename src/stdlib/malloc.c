/*
 * malloc.c
 *
 * Allocate an uninitialized block of memory from the default heap.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

void *malloc(size_t size)
{
    void *p = _alloc((uint16_t)&_heap, size);
    if (p == NULL)
        errno = ENOMEM;
    return p;
}
