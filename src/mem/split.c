/*
 * split.c
 *
 * Split memory block to two blocks.
 *
 * 05.07.2023   tstih
 *
 */
#include <string.h>
#include <mem/mem.h>

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