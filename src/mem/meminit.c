/*
 * meminit.c
 *
 * Memory allocation system initialization.
 *
 * 05.07.2023   tstih
 *
 */
#include <string.h>
#include <mem/mem.h>

void _memory_init()
{
    /* Calculate free memory */
    uint16_t size=_memtop() - (uint16_t)&_heap;
    _heap_init((uint16_t)&_heap,size);
}