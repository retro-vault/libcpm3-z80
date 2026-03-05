/*
 * split.c
 *
 * Split a heap block into two blocks.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.03.2026   tstih
 *
 */
#include <mem/mem.h>

void _split(block_t *b, uint16_t size)
{
    block_t *nw = (block_t *)(b->data + size);
    nw->hdr.next = b->hdr.next;
    nw->size = b->size - (size + BLK_SIZE);
    nw->stat = b->stat;
    b->size = size;
    b->hdr.next = nw;
}
