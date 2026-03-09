/*
 * fd_def.c
 *
 * Define the internal table that stores active file descriptors.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

/* Tiny descriptor table just contains pointers. */
_fd_t* _fds[MAX_FILES];
