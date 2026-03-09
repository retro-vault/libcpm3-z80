/*
 * creat.c
 *
 * Create or truncate a file for write-only access.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <fcntl.h>

int creat(const char *pathname) {
    /* According to Posix, open does it all. */
    return open(pathname, O_WRONLY|O_CREAT|O_TRUNC);
}
