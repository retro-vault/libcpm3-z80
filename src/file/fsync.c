/*
 * fsync.c
 *
 * Posix C file flush.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 12.08.2021   tstih
 *
 */
#include <errno.h>
#include <sys/bdos.h>
#include <file/fd.h>


int fsync(int fd) {

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* All done! */
    if (!fdblk->dmadirty) {
        errno = 0; 
        return 0;
    }

    /* Make sure DMA is set correctly. */
    bdos(F_DMAOFF,(uint16_t)&(fdblk->dma));

    /* Write last block! */
    bdos_ret_t ret;
    bdosret(F_WRITE,(uint16_t)&(fdblk->fcb),&ret);
    if (ret.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* But beware, you have to return to 
       this block. So get its data back to FCB! */
    bdosret(F_RANDREC,(uint16_t)&(fdblk->fcb),&ret);
    if (ret.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* We're no longer dirty! */
    fdblk->dmadirty=false;

    /* If we're here, we're queer. */
    errno = 0;
    return 0;
}