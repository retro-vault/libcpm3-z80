/*
 * stdio.c
 *
 * Standard Library implementation.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 28.04.2021   tstih
 *
 */
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <util/print.h>

#include <sys/bdos.h>
#include <sys/types.h>

#include <file/fd.h>

static bool check_fp(FILE *fp) {
    return fp!=NULL && _fd_get(fp->fd)!=NULL;
}

FILE *fopen(const char *path, const char *mode)
{
    int fd, oflags;
    FILE *f;

    /* Reset errno. */
    errno = 0;

    /* Initialize oflags. */
    oflags=0;

    /* Extract mode. */
    if (strncmp(mode, "r", 1) == 0) {
        oflags = O_RDONLY;
    }

    if (strncmp(mode, "w", 1) == 0) {
        oflags = O_WRONLY | O_TRUNC;
    }

    if (strncmp(mode, "r+", 2) == 0) {
        oflags = O_RDWR;
    }

    if (strncmp(mode, "w+", 2) == 0) {
        oflags = O_RDWR | O_TRUNC;
    }

    /* Open file. */
    fd = open(path, oflags);
    if (fd < 0) return NULL; /* errno is set by open... */

    /* Create FILE * structure. */
    f=malloc(sizeof(FILE));
    f->fd=fd;
    f->eof=false;
    memset(f->flags, 0, 4);
    strncpy((const char *) f->flags, (const char *) mode, 3);

    /* And return. */
    return f;
}

int fclose(FILE *fp)
{
    /* Reset errno. */
    errno = 0;

    /* Make sure fp is valid file. */
    if (!check_fp(fp)) {
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

size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    /* Reset errno. */
    errno = 0;

    int i = 0;
    ssize_t wr = 0;
    unsigned char * data = (unsigned char *) ptr;

    /* Make sure fp is valid file. */
    if (!check_fp(fp)) {
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

int feof(FILE *fp)
{
    /* Make sure fp is valid file. */
    if (!check_fp(fp)) {
        errno = EBADF;
        return -1;
    } else 
        return (fp->eof) ? 1 : 0;
}

int fseek(FILE *fp, long offset, int whence)
{
    /* Reset errno. */
    errno = 0;

    /* Must be fvalid file pointer. */
    if (!check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    /* Try... */
    if (lseek(fp->fd, offset, whence) == -1) return -1;

    /* We're good. */
    fp->eof=false;
    return 0;
}

long ftell(FILE *fp) {
    if (!check_fp(fp)) {
        errno = EBADF;
        return -1;
    } else {
        fd_t* pfd = _fd_get(fp->fd);
        return pfd->fpos;
    }
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    char *data = (char*) ptr;
    int rd;
    ssize_t cnt=0;
    char *eof = NULL; 

    /* Reset errno. */
    errno = 0;

    /* Make sure fd is valid. */
    if (!check_fp(fp)) {
        errno = EBADF;
        return -1;
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
        else if (rd == -1) 
            return 0; /* errno is propagated. */
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
            return cnt;
        }
    }
    return cnt;
}

int fgetc(FILE *fp) {

    /* Reset errno. */
    errno = 0;

    /* Check file descriptor. */
    if (!check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    /* If eof, don't proceed. */
    if (fp->eof) return 0;
    
    /* Read char. */
    char ch;
    int rd = read(fp->fd, &ch, 1);
    if (rd == 0) {
        fp->eof = true;
        return 0;
    }
    else if (rd == -1) 
        return -1; /* errno is propagated. */
    else if (rd == 1) {
        /* If text mode file, check eof... */
        if (memchr(&fp->flags, 'b', 3) == NULL && ch==EOF) {
            fp->eof = true;
            return 0;
        } 
    }
    return ch;
}


int putchar(int c) {
    /* Extend newline if DOS. */
    if (c=='\n') {
        switch(nltype) {
            case NL_LF:
                bdos(C_WRITE,'\n');
                break;
            case NL_CRLF:
                bdos(C_WRITE,'\r');
                bdos(C_WRITE,'\n');
                break;
            case NL_LFCR:
                bdos(C_WRITE,'\n');
                bdos(C_WRITE,'\r');
                break;
        }
    } else bdos(C_WRITE,c);
    return c;
}

int puts(const char *s)
{
   int i = 0;
   while(s[i]) { putchar(s[i]); i++; }
   return 1;
}

int printf(char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(NULL, fmt, ap);
	va_end(ap);
	return r;
}

int sprintf(char *buf, char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(&buf, fmt, ap);
	va_end(ap);
	return r;
}