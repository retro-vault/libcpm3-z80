/*
 * _to_fcb_name.c
 *
 * Convert a C filename fragment to blank-padded CP/M FCB name format.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fcb.h>

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
