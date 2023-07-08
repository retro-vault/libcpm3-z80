#include <stdio/_stdio.h>

bool _check_fp(FILE *fp) {
    return fp!=NULL && _fd_get(fp->fd)!=NULL;
}