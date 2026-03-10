/*
 * _split.c
 *
 * Split a larger free heap block into an allocated part and
 * a remaining free part, updating the block list links.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_mem.h"

void _split(_block_t *b, uint16_t size)
{
    _block_t *nw = (_block_t *)(b->data + size);
    nw->hdr.next = b->hdr.next;
    nw->size = b->size - (size + BLK_SIZE);
    nw->stat = b->stat;
    b->size = size;
    b->hdr.next = nw;
}
