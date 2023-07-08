/*
 * heapinit.c
 *
 * Initialize the heap.
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
    first->size = size - BLK_SIZE;
    first->stat = NEW;
}