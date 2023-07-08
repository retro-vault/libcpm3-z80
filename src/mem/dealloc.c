/*
 * dealloc.c
 *
 * Deallocate a memory block on the heap.
 *
 * 05.07.2023   tstih
 *
 */
#include <string.h>
#include <mem/mem.h>

void _dealloc(uint16_t heap, void *p)
{
    block_t *prev;
    block_t *b;

    /* calculate block address from pointer */
    b = (block_t *)((uint16_t)p - BLK_SIZE);

    /* make sure it is a valid memory block by finding it */
    if (_list_find((list_header_t *)heap, (list_header_t **)&prev, _list_match_eq, (uint16_t)b))
    {
        b->stat = NEW;
        /* merge 3 blocks if possible */
        if (prev && !(prev->stat & ALLOCATED))
        { /* try previous */
            _merge_with_next(prev);
            b = prev;
        }
        /* try next */
        if (b->hdr.next && !(((block_t *)(b->hdr.next))->stat & ALLOCATED))
            _merge_with_next(b);
    }
}