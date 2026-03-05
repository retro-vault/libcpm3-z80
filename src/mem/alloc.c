/*
 * alloc.c
 *
 * Allocate a memory block on the heap.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.03.2026   tstih
 *
 */
#include <mem/mem.h>

static uint8_t _match_free(list_header_t *p, uint16_t size)
{
    block_t *b = (block_t *)p;
    return !(b->stat & ALLOCATED) && b->size >= size;
}

void *_alloc(uint16_t heap, size_t size)
{
    block_t *prev;
    block_t *b = (block_t *)_list_find(
        (list_header_t *)heap,
        (list_header_t **)&prev,
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
