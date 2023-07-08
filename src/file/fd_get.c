/*
 * fd_get.c
 *
 * file descriptor get slot value
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2021   tstih
 *
 */
#include <file/fd.h>

fd_t* _fd_get(int fd) {
    if (fd < 3 || fd >= MAX_FILES)
        return NULL;
    else
        return _fds[fd];
}