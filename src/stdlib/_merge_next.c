/*
 * _merge_next.c
 *
 * Merge a free heap block with the next adjacent free block.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_mem.h"

void _merge_with_next(_block_t *b)
{
    _block_t *bnext = (_block_t *)b->hdr.next;
    b->size += (BLK_SIZE + bnext->size);
    b->hdr.next = bnext->hdr.next;
}
