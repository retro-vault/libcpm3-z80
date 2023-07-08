/*
 * fd_reserve.c
 *
 * allocate new file descriptor
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2021   tstih
 *
 */
#include <file/fd.h>

int _fd_reserve() {
    uint8_t fd=3;
    while (fd<MAX_FILES && _fds[fd]!=NULL) fd++;
    if (fd==MAX_FILES)
        return -1;
    else
        return fd;
}