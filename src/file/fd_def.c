/*
 * fd_def.c
 *
 * file descriptor definition.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2021   tstih
 *
 */
#include <file/fd.h>

/* Tiny descriptor table just contains pointers. */
fd_t* _fds[MAX_FILES];