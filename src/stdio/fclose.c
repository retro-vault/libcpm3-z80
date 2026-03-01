/*
 * fclose.c
 *
 * fclose function (see:stdio.h)
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int fclose(FILE *fp)
{
    /* Reset errno. */
    errno = 0;

    /* Make sure fp is valid file. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    /* Do not close standard streams. */
    if (fp->fd >= 0 && fp->fd <= 2) {
        errno = EINVAL;
        return -1;
    }

    /* If fp is valid, then close. */
    if (close(fp->fd) == -1)
        return -1;

    /* And release fp. */
    free(fp);

    /* Return. */
    return 0;
}
