/*
 * malloc.c
 *
 * malloc function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void *malloc(size_t size)
{
    return _alloc((uint16_t)&_heap,size);
}