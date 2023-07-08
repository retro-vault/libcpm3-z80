#include <file/fd.h>

void _fd_free(int fd) {
    _fds[fd]=NULL;
}