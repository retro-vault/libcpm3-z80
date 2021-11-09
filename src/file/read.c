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
#include <string.h>
#include <unistd.h>

#include <sys/bdos.h>
#include <sys/types.h>
#include <file/fcb.h>
#include <file/fd.h>

#undef DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif 

ssize_t read(int fd, void *buf, size_t count) {

    /* If DMA dirty then write. */
    fsync(fd);

    /* We'll need bytes */
    uint8_t *bbuf=(uint8_t*)buf;

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Fetch the data sequentially! */
    size_t bread=0;
    while (bread < count) {
        /* Is DMA block empty? */
        if (fdblk->dmapos==DMA_INVALID_POS) {
            /* First set the DMA to our block!*/
            bdos(F_DMAOFF,(uint16_t)&(fdblk->dma));
            /* Now read next disk block */
            bdos_ret_t result;
            bdosret(F_READ,(uint16_t)&(fdblk->fcb),&result);
            if (result.reta==1)  /* end of file? */
                return bread;
            else if (result.reta!=0) { /* error */ 
                errno=EIO;
                return -1;
            }
            /* If we are here the read was a success,
               set dmapos to valid value. */
            fdblk->dmapos=0;
        }

        /* How many bytes left to read? */
        size_t left = count - bread;
        /* If more then available in the DMA, just
           read what we have in the DMA */
        if (left > (DMA_SIZE - fdblk->dmapos))
            left = DMA_SIZE - fdblk->dmapos;

        /* And copy from DMA */
        memcpy(&(bbuf[bread]), &(fdblk->dma[fdblk->dmapos]), left );
        /* Update DMA position */
        fdblk->dmapos+=left;
        /* And current file position. */
        fdblk->fpos+=left;
        /* Did we reach the end of DMA block? */
        if (fdblk->dmapos==DMA_SIZE)
            fdblk->dmapos=DMA_INVALID_POS;
        bread+=left;
    }
    /* If we did not read anything, and it is an eof
       return 0. Else return bytes read. */
    errno=0;
    return bread;
}