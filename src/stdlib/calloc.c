/*
 * calloc.c
 *
 * Allocate zero-initialized storage for an array of objects.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

void *calloc(size_t num, size_t size)
{
    if (size != 0 && num > ((size_t)-1) / size)
        return NULL;
    size_t bytes = num * size;
    void *result = malloc(bytes);
    if (result!=NULL)
        memset(result, 0, bytes);
    return result;
}
