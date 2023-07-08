/*
 * free.c
 *
 * free function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void free(void *p)
{
    _dealloc((uint16_t)&_heap,p);
}