#include <stdio/_stdio.h>

size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    /* Reset errno. */
    errno = 0;

    int i = 0;
    ssize_t wr = 0;
    unsigned char * data = (unsigned char *) ptr;

    /* Make sure fp is valid file. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    for (i = 0; i < nmemb; i++) 
        if ((wr = write(fp->fd, data, size))==-1) 
            return 0;

    /* Return. */
    fp->eof=false;
    return i;
}