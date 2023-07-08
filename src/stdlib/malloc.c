#include <stdlib/_stdlib.h>

void *malloc(size_t size)
{
    return _alloc((uint16_t)&_heap,size);
}