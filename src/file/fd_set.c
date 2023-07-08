#include <file/fd.h>

void _fd_set(int fd, fd_t *fdblk) {
    _fds[fd]=fdblk;
}