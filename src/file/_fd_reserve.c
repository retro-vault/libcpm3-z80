/*
 * _fd_reserve.c
 *
 * Find and reserve a free file-descriptor slot in the table.
 * Returns a slot index or -1 when all slots are occupied.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <file/_fd.h>

int _fd_reserve(void) {
    uint8_t fd=3;
    while (fd<MAX_FILES && _fds[fd]!=NULL) fd++;
    if (fd==MAX_FILES)
        return -1;
    else
        return fd;
}
