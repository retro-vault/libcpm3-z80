#include <stdlib/_stdlib.h>

void free(void *p)
{
    _dealloc((uint16_t)&_heap,p);
}