/*
 * lseek.c
 *
 * Posix C file lseek function. 
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
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/bdos.h>
#include <sys/types.h>
#include <file/fcb.h>
#include <file/fd.h>

off_t lseek(int fd, off_t offset, int whence) {

    /* If dirty, write. */
    if (fsync(fd) == -1)
        return -1;

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Resolve absolute offset from whence. */
    off_t abs_offset;
    if (whence == SEEK_SET) {
        abs_offset = offset;
    } else if (whence == SEEK_CUR) {
        abs_offset = fdblk->fpos + offset;
    } else {
        /* SEEK_END: not supported on CP/M (file size not directly
           available from FCB without a separate F_SIZE call). */
        errno = EINVAL;
        return -1;
    }

    if (abs_offset < 0) {
        errno = EINVAL;
        return -1;
    }

    /* Calculate random record and intra-record offset. */
    long rec     = abs_offset / DMA_SIZE;
    long dmaoffs = abs_offset % DMA_SIZE;
    fdblk->fcb.rrec = (uint16_t)rec;

    /* Seek to the record. */
    bdos(F_DMAOFF,(uint16_t)&(fdblk->dma));
    bdos_ret_t result;
    bdosret(F_READRAND,(uint16_t)&(fdblk->fcb),&result);
    if (result.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* Update file pointers. */
    fdblk->fpos    = abs_offset;
    fdblk->dmapos  = (uint8_t)dmaoffs;

    errno = 0;
    return abs_offset;
}
