/*
 * _fd_free.c
 *
 * Clear a reserved file-descriptor slot in the internal table.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

void _fd_free(int fd) {
    if (fd >= 0 && fd < MAX_FILES)
        _fds[fd]=NULL;
}
