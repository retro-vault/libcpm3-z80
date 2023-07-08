#include <string.h>

void *memset(void *s, int c, size_t n) {
    unsigned char *s_ = s;
    const unsigned char c_ = (unsigned char)c;
    for (size_t i = 0; i < n; ++i) {
        s_[i] = c_;
    }
    return s;
}