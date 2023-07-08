/*
 * merge_next.c
 *
 * Merge block with next block.
 *
 * 05.07.2023   tstih
 *
 */
#include <string.h>
#include <mem/mem.h>

void _merge_with_next(block_t *b)
{
    block_t *bnext = b->hdr.next;
    b->size += (BLK_SIZE + bnext->size);
    b->hdr.next = bnext->hdr.next;
}
