/*
 * strerror.c
 *
 * Return a human-readable message string for an errno value.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <errno.h>

char *strerror(int en)
{
    switch(en) {
    case 0:
        return (const char *) "Success";
        break;
    case ENOENT:
        return (const char *) "No such file or directory";
        break;
    case EIO:
        return (const char *) "I/O error";
        break;
    case EBADF:
        return (const char *) "Bad file descriptor";
        break;
    case EINVAL:
        return (const char *) "Illegal address";
        break;
    case ENFILE:
        return (const char *) "File table overflow";
        break;
    case EAGAIN:
        return (const char *) "Try again";
        break;
    }
    /* if we're here, we're toast */
    return "Unknown error!";
}
