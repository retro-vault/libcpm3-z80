#include <string.h>

char *strcpy(char *dest, const char *src)
{
    size_t index = 0;

    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }

    return (dest);
}