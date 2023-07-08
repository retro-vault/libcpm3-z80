#include <string.h>
#include <mem/mem.h>

uint8_t _match_free_block(list_header_t *p, uint16_t size)
{
    block_t *b = (block_t *)p;
    return !(b->stat & ALLOCATED) && b->size >= size;
}

