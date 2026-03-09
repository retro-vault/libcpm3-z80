/*
 * _alloc.c
 *
 * Allocate a block from an internal heap arena given a size.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <_impl/mem/_mem.h>

static uint8_t _match_free(_list_header_t *p, uint16_t size)
{
    _block_t *b = (_block_t *)p;
    return !(b->stat & ALLOCATED) && b->size >= size;
}

void *_alloc(uint16_t heap, size_t size)
{
    _block_t *prev;
    _block_t *b = (_block_t *)_list_find(
        (_list_header_t *)heap,
        (_list_header_t **)&prev,
        _match_free,
        (uint16_t)size);

    if (b) {
        if (b->size - size > BLK_SIZE + MIN_CHUNK_SIZE)
            _split(b, size);
        b->stat = ALLOCATED;
        return b->data;
    }
    return NULL;
}
