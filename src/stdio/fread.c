/*
 * fread.c
 *
 * Read nmemb objects of size bytes from a stream into a buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    char *data = (char*) ptr;
    int rd;
    ssize_t cnt=0;
    char *eof = NULL; 

    /* Reset errno. */
    errno = 0;

    /* Make sure fd is valid. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        if (fp)
            fp->err = true;
        return 0;
    }

    /* If eof, don't proceed. */
    if (fp->eof) return 0;

    /* Read! */
    for (int i = 0; i < nmemb; i++) {
        rd = read(fp->fd, data, size);
        if (rd == 0) {
            fp->eof = true;
            return cnt;
        }
        else if (rd == -1) {
            fp->err = true;
            return 0; /* errno is propagated. */
        }
        else if (rd == size) {
            /* If text mode file, find eof... */
            if (memchr(&fp->flags, 'b', 3) == NULL) {
                eof = memchr(data, EOF, rd);
                if (eof) {
                    fp->eof = true;
                    return cnt;
                }
            }
            data += rd;
            cnt++;
        } else {
            errno = EIO;
            fp->err = true;
            return cnt;
        }
    }
    fp->err = false;
    return cnt;
}
