/*
 * fd_set.c
 *
 * assign file descriptor
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2021   tstih
 *
 */
#include <file/fd.h>

void _fd_set(int fd, fd_t *fdblk) {
    _fds[fd]=fdblk;
}