/*
 * dealloc.c
 *
 * Deallocate a memory block on the heap.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.03.2026   tstih
 *
 */
#include <mem/mem.h>

void _dealloc(uint16_t heap, void *p)
{
    block_t *prev;
    block_t *b;

    if (!p)
        return;

    b = (block_t *)((uint16_t)p - BLK_SIZE);

    if (!_list_find(
            (list_header_t *)heap,
            (list_header_t **)&prev,
            _list_match_eq,
            (uint16_t)b))
        return;

    b->stat = NEW;

    if (prev && !(((block_t *)prev)->stat & ALLOCATED)) {
        _merge_with_next((block_t *)prev);
        b = (block_t *)prev;
    }

    if (b->hdr.next && !(((block_t *)(b->hdr.next))->stat & ALLOCATED))
        _merge_with_next(b);
}
