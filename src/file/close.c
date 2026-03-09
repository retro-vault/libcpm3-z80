/*
 * close.c
 *
 * Close an open CP/M file descriptor and release its resources.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/bdos.h>
#include <file/_fcb.h>
#include <file/_fd.h>

int close(int fd) {

    /* Get the descriptor. */
    _fd_t* fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Flush dirty DMA block. */
    if (fdblk->dmadirty && fsync(fd) == -1)
        return -1;

    /* Call file close on BDOS 
       TODO: Manage hardware error. */
    bdos_ret_t ret;
    bdosret(F_CLOSE,(uint16_t)&(fdblk->fcb),&ret);
    if (ret.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* Finally, release the file descriptor. */
    _fd_set(fd,NULL);

    /* Free the memory. */
    free(fdblk);

    /* And return success. */
    errno = 0;
    return 0;
}
