#include <stdlib/_stdlib.h>

#ifndef LEAN_AND_MEAN

unsigned long _next = 1;

int rand(void) /* RAND_MAX assumed to be 32767 */
{
    _next = _next * 1103515245 + 12345;
    return (unsigned int)(_next / 65536) % 32768;
}

#else 

unsigned int _next = 1;

int rand(void) /* RAND_MAX assumed to be 32767 */
{
    _next = _next * 753 + 22444;
    return (unsigned int)(_next % 32768);
}

#endif /* LEAN_AND_MEAN */