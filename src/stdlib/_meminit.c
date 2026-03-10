/*
 * _meminit.c
 *
 * Initialize the default heap used by malloc() and free().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

#include "_mem.h"

void _memory_init(void)
{
    /* Calculate free memory */
    uint16_t size=_memtop() - (uint16_t)&_heap;
    _heap_init((uint16_t)&_heap,size);
}
