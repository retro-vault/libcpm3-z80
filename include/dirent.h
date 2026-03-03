/*
 * dirent.h
 *
 * POSIX-like directory enumeration.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 11.08.2021   tstih
 *
 */
#ifndef LIBCPM3_DIRENT_H
#define LIBCPM3_DIRENT_H

typedef void * DIR;             /* Dir is a private structure. */

struct dirent {
    unsigned char  d_type;      /* CP/M type */
    char           d_name[256]; /* filename */
};

DIR* opendir(const char *);
int closedir(DIR *);
struct dirent* readdir(DIR *);

#endif /* LIBCPM3_DIRENT_H */