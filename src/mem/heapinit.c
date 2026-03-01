/*
 * heapinit.c
 *
 * Initialize the heap.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2023   tstih
 *
 */
#include <string.h>
#include <mem/mem.h>

void _heap_init(uint16_t start, uint16_t size) {
    /* First block is the heap. s*/
    block_t *first = (block_t *)start;
    first->hdr.next = NULL;
    if (size <= BLK_SIZE)
        first->size = 0;
    else
        first->size = size - BLK_SIZE;
    first->stat = NEW;
}
