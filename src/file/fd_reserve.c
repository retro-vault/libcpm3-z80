#include <file/fd.h>

int _fd_reserve() {
    uint8_t fd=3;
    while (fd<MAX_FILES && _fds[fd]!=NULL) fd++;
    if (fd==MAX_FILES)
        return -1;
    else
        return fd;
}