#include <stdlib/_stdlib.h>

void srand(unsigned int seed)
{
    _next = seed;
}