#include <string.h>

char *strrchr(char *s, int c)
{
    char *ptr = (const char *) s;
    char *retptr = NULL;

    while (ptr[0] != '\0') {
        if (ptr[0] == c) {
            retptr = (char *) ptr;
        }
        ptr ++;
    }
    return retptr;
}