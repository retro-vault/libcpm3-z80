/*
 * merge_next.c
 *
 * Merge a heap block with its successor.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.03.2026   tstih
 *
 */
#include <mem/mem.h>

void _merge_with_next(block_t *b)
{
    block_t *bnext = (block_t *)b->hdr.next;
    b->size += (BLK_SIZE + bnext->size);
    b->hdr.next = bnext->hdr.next;
}
