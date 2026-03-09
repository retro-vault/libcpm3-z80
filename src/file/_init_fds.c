/*
 * _init_fds.c
 *
 * Initialize the internal file-descriptor table used by the library.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

/* Initialize file descriptors:
   all descriptors are NULL, except stdin, stdout, sterr. */
void _init_fds(void) {
    for (uint8_t i=0; i<MAX_FILES; i++) _fds[i]=NULL;
}
