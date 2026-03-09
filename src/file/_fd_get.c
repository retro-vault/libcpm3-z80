/*
 * _fd_get.c
 *
 * Return the internal descriptor record for a file descriptor index.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

_fd_t* _fd_get(int fd) {
    if (fd < 3 || fd >= MAX_FILES)
        return NULL;
    else
        return _fds[fd];
}
