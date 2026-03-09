/*
 * ferror.c
 *
 * Test whether the stream error indicator is set.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int ferror(FILE *fp) {
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }
    return fp->err ? 1 : 0;
}
