/*
 * free.c
 *
 * Release a block previously returned by malloc() or calloc().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

void free(void *p)
{
    if (p == NULL)
        return;
    _dealloc((uint16_t)&_heap,p);
}
