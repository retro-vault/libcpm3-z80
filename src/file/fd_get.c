#include <file/fd.h>

fd_t* _fd_get(int fd) {
    if (fd < 3 || fd >= MAX_FILES)
        return NULL;
    else
        return _fds[fd];
}