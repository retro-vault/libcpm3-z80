/*
 * _dealloc.c
 *
 * Return a previously allocated block to an internal heap arena.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_mem.h"

void _dealloc(uint16_t heap, void *p)
{
    _block_t *prev;
    _block_t *b;

    if (!p)
        return;

    b = (_block_t *)((uint16_t)p - BLK_SIZE);

    if (!_list_find(
            (_list_header_t *)heap,
            (_list_header_t **)&prev,
            _list_match_eq,
            (uint16_t)b))
        return;

    b->stat = NEW;

    if (prev && !(((_block_t *)prev)->stat & ALLOCATED)) {
        _merge_with_next((_block_t *)prev);
        b = (_block_t *)prev;
    }

    if (b->hdr.next && !(((_block_t *)(b->hdr.next))->stat & ALLOCATED))
        _merge_with_next(b);
}
