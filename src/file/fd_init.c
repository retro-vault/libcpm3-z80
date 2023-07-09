/*
 * fd_init.c
 *
 * Initialize file descriptors.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2023   tstih
 *
 */
#include <file/fd.h>

/* Initialize file descriptors:
   all descriptors are NULL, except stdin, stdout, sterr. */
void _init_fds(void) {
    for (uint8_t i=0; i<MAX_FILES; i++) _fds[i]=NULL;
}
