/*
 * creat.c
 *
 * Posix C file create new file.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 12.08.2021   tstih
 *
 */
#include <fcntl.h>

int creat(const char *pathname) {
    /* According to Posix, open does it all. */
    return open(pathname, O_WRONLY|O_CREAT|O_TRUNC);
}