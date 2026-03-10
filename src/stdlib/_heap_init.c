/*
 * _heap_init.c
 *
 * Initialize a heap arena header at the supplied memory address.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

#include "_mem.h"

void _heap_init(uint16_t start, uint16_t size) {
    /* First block is the heap. s*/
    _block_t *first = (_block_t *)start;
    first->hdr.next = NULL;
    if (size <= BLK_SIZE)
        first->size = 0;
    else
        first->size = size - BLK_SIZE;
    first->stat = NEW;
}
