/*
 * fcb.c
 *
 * CP/M file control block.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <file/fcb.h>

void _to_fcb_name(char *dst, char *src, uint8_t maxlen) {
    char c;
    uint8_t idx;
    /* Pure ascii, uppercase, and space padded. */
    for (idx = 0; (idx < maxlen) && (src[idx] != '\0'); idx++) {
        c = src[idx] & 0x7F;
        if (c >= 0x61 && c <= 0x7a)
            c -= 0x20;
        dst[idx] = c;
    }
    while (idx < maxlen) {
        dst[idx] = ' '; // Pad the filename
        idx++;
    }
}