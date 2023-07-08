#include <string.h>
#include <mem/mem.h>

void *_alloc(uint16_t heap, size_t size)
{
    block_t *prev;
    block_t *b;

    b = (block_t *)_list_find(
        (list_header_t *)heap,
        (list_header_t **)&prev,
        _match_free_block, size);

    if (b)
    {
        if (b->size - size > BLK_SIZE + MIN_CHUNK_SIZE)
            _split(b, size);
        b->stat = ALLOCATED;
        return b->data;
    }
    else
        return NULL;
}