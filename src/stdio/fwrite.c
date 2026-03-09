/*
 * fwrite.c
 *
 * Write nmemb objects of size bytes from a buffer to a stream.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    /* Reset errno. */
    errno = 0;

    int i = 0;
    ssize_t wr = 0;
    const unsigned char * data = (const unsigned char *) ptr;

    /* Make sure fp is valid file. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        if (fp)
            fp->err = true;
        return 0;
    }

    for (i = 0; i < nmemb; i++) {
        if ((wr = write(fp->fd, data, size)) == -1) {
            fp->err = true;
            return 0;
        }
        data += size;
    }

    /* Return. */
    fp->eof=false;
    fp->err=false;
    return i;
}
