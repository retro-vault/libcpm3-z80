/*
 * mem.c
 *
 * Memory management utility functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 25.05.2012   tstih
 *
 */
#include <string.h>
#include <util/mem.h>

uint8_t _match_free_block(list_header_t *p, uint16_t size)
{
    block_t *b = (block_t *)p;
    return !(b->stat & ALLOCATED) && b->size >= size;
}

void _merge_with_next(block_t *b)
{
    block_t *bnext = b->hdr.next;
    b->size += (BLK_SIZE + bnext->size);
    b->hdr.next = bnext->hdr.next;
}

void _split(block_t *b, uint16_t size)
{
    block_t *nw;
    nw = (block_t *)((uint16_t)(b->data) + size);
    nw->hdr.next = b->hdr.next;
    nw->size = b->size - (size + BLK_SIZE);
    nw->stat = b->stat;
    /* do not set owner and stat because
	   they'll be populated later */
    b->size = size;
    b->hdr.next = nw;
}

void _memory_init()
{
    /* Calculate free memory */
    uint16_t size=(_memtop()) - (uint16_t)&_heap;

    /* First block is the heap. s*/
    block_t *first = (block_t *)&_heap;
    first->hdr.next = NULL;
    first->size = size - BLK_SIZE;
    first->stat = NEW;
}