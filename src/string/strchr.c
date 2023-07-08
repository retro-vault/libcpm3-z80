#include <string.h>

char *strchr(const char *s, int c) {
    const char c_ = (char)c;
    do {
        if (*s == c_) {
            return (char *)s;
        }
    } while (*s++ != '\0');
    return NULL;
}