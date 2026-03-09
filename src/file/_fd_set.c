/*
 * _fd_set.c
 *
 * Store an internal descriptor record in a file-descriptor slot.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

void _fd_set(int fd, _fd_t *fdblk) {
    if (fd >= 0 && fd < MAX_FILES)
        _fds[fd]=fdblk;
}
