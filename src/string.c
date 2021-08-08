/*
 * string.c
 *
 * idp standard C library implementation
 * 
 * NOTES:
 *  the idp standard library is based on the cpmlibc
 *  https://github.com/dmo9000/cpmlibc
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 27.04.2021   tstih
 *
 */
#include <errno.h>
#include <ctype.h>
#include <string.h>

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *s_ = s;
    const unsigned char c_ = (unsigned char)c;

    for (size_t i = 0; i < n; ++i) {
        if (s_[i] == c_) {
            return (void *)(s_ + i);
        }
    }

    return NULL;
}

int memcmp(const void *lhs, const void *rhs, size_t count) {
    const unsigned char *lhs_ = lhs;
    const unsigned char *rhs_ = rhs;

    for (size_t i = 0; i < count; ++i) {
        const int res = lhs_[i] - rhs_[i];
        if (res != 0) {
            return res;
        }
    }

    return 0;
}

void *memcpy(void *s1, const void *s2, size_t n) {
    unsigned char *s1_ = s1;
    const unsigned char *s2_ = s2;
    for (size_t i = 0; i < n; ++i) {
        s1_[i] = s2_[i];
    }

    return s1;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *s_ = s;
    const unsigned char c_ = (unsigned char)c;
    for (size_t i = 0; i < n; ++i) {
        s_[i] = c_;
    }
    return s;
}

size_t strlen(const char *str)
{
    size_t length = 0;

    while (*str++)
        length++;

    return (length);
}

char *strcpy(char *dest, const char *src)
{
    size_t index = 0;

    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }

    return (dest);
}

char* strncpy(char* dst, const char* src, size_t num)
{
    if (dst == NULL) {
        return NULL;
    }
    char* ptr = dst;
    while (*src && num--)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return ptr;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, register size_t n)
{
  register unsigned char u1, u2;
  while (n-- > 0)
    {
      u1 = (unsigned char) *s1++;
      u2 = (unsigned char) *s2++;
      if (u1 != u2)
        return u1 - u2;
      if (u1 == '\0')
        return 0;
    }
  return 0;
}

char *strchr(const char *s, int c) {
    const char c_ = (char)c;
    do {
        if (*s == c_) {
            return (char *)s;
        }
    } while (*s++ != '\0');
    return NULL;
}

char *strrchr(char *s, int c)
{
    char *ptr = (const char *) s;
    char *retptr = NULL;

    while (ptr[0] != '\0') {
        if (ptr[0] == c) {
            retptr = (char *) ptr;
        }
        ptr ++;
    }
    return retptr;
}

char * strsep(char **stringp, const char *delim)
{
    char *s;
    const char *spanp;
    int c, sc;
    char *tok;
    if ((s = *stringp) == NULL)
        return (NULL);
    for (tok = s;;) {
        c = *s++;
        spanp = delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                *stringp = s;
                return (tok);
            }
        } while (sc != 0);
    }
}

size_t strcspn(const char *s1, const char *s2) {
    size_t res = 0;
    while (*s1 != '\0') {
        if (strchr(s2, *s1) == NULL) {
            ++s1;
            ++res;
        } else {
            return res;
        }
    }
    return res;
}

char *strtok(char *s, const char *delim) {
    static char *last;

    if (s == NULL) {
        s = last;
    }
    int ch;
    do {
        ch = *s++;
        if (ch == '\0') {
            return NULL;
        }
    } while (strchr(delim, ch));
    --s;
    last = s + strcspn(s, delim);
    if (*last != '\0') {
        *last++ = '\0';
    }
    return s;
}

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
    case E2BIG:
        return (const char *) "Argument list too long";
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
    case ENOTTY:
        return (const char *) "Not a typewriter";
        break;
    case EPIPE:
        return (const char *) "Transport endpoint not connected";
        break;
    case EAGAIN:
        return (const char *) "Try again";
        break;
    }
    /* if we're here, we're toast */
    return "Unknown error!";
}

void stoupper(char *s)
{
    for(; *s; s++)
        *s=toupper(*s);
}

void stolower(char *s)
{
    for(; *s; s++)
        *s=tolower(*s);
}