#include <string.h>

void *memcpy(void *s1, const void *s2, size_t n) {
    unsigned char *s1_ = s1;
    const unsigned char *s2_ = s2;
    for (size_t i = 0; i < n; ++i) {
        s1_[i] = s2_[i];
    }

    return s1;
}