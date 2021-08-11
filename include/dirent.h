/*
 * dirent.h
 *
 * Unixish like functionality for enumerating files
 * and folders.
 * 
 * NOTES:
 *  Not implemented yet, planned for 15.08.2021
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 11.08.2021   tstih
 *
 */
#ifndef __DIRENT_H__
#define __DIRENT_H__

typedef void * DIR;             /* Dir is a private structure. */

struct dirent {
    unsigned char  d_type;      /* CP/M type */
    char           d_name[256]; /* filename */
};

DIR* opendir(const char *);
int closedir(DIR *);
struct dirent* readdir(DIR *);

#endif /* __DIRENT_H__ */