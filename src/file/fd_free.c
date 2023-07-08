/*
 * fd_free.c
 *
 * file descriptor free slot
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2021   tstih
 *
 */
#include <file/fd.h>

void _fd_free(int fd) {
    _fds[fd]=NULL;
}