/*
 * calloc.c
 *
 * calloc function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void *calloc(size_t num, size_t size)
{
    size_t bytes = num * size;
    void *result = malloc(bytes);
    if (result!=NULL)
        memset(result, 0, bytes);
    return result;
}