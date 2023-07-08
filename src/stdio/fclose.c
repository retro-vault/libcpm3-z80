/*
 * fclose.c
 *
 * fclose function (see:stdio.h)
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

    /* If fp is valid, then close. */
    close(fp->fd);

    /* And release fp. */
    free(fp);

    /* Return. */
    return 0;
}