/*
 * fd.c
 *
 * Posix file descriptors.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <file/fd.h>

/* Tiny descriptor table just contains pointers. */
static fd_t* _fds[MAX_FILES];

/* Initialize file descriptors:
   all descriptors are NULL, except stdin, stdout, sterr. */
void _init_fds() {
    for (uint8_t i=0; i<MAX_FILES; i++) _fds[i]=NULL;
}

int _fd_reserve() {
    uint8_t fd=3;
    while (fd<MAX_FILES && _fds[fd]!=NULL) fd++;
    if (fd==MAX_FILES)
        return -1;
    else
        return fd;
}

void _fd_free(int fd) {
    _fds[fd]=NULL;
}

void _fd_set(int fd, fd_t *fdblk) {
    _fds[fd]=fdblk;
}


fd_t* _fd_get(int fd) {
    if (fd < 3 || fd >= MAX_FILES)
        return NULL;
    else
        return _fds[fd];
}