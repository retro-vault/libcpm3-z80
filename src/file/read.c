/*
 * read.c
 *
 * Posix C file read function
 * 
 * NOTE:
 *  No need to check for SSIZE_MAX because count is 16bit.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/bdos.h>
#include <sys/types.h>
#include <file/fcb.h>
#include <file/fd.h>

ssize_t read(int fd, void *buf, size_t count) {
    buf;

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Fetch the data sequentially! */
    size_t bread=0;
    bool eof=false;
    while (!eof && bread < count) {
        size_t left = count - bread;
        if ( left < (DMA_SIZE - fdblk->dmapos) ) {
            /* We're done reading. Move to buffer,
               and conclude! */
            
        } else {
            /* Move everything to buffer, and
               read next block. */
        }
    }

    /* If we did not read anything, and it is an eof
       return 0. Else return bytes read. */
    return bread;
}