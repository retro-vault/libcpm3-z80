/*
 * dirent.c
 *
 * Implement CP/M directory iteration with wildcard searches.
 * Provides opendir(), readdir(), and closedir() over CP/M BDOS.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/bdos.h>
#include <file/_fcb.h>

typedef struct _dir_s {
    _fcb_t fcb;
    uint8_t dma[128];
    struct dirent entry;
} _dir_t;

static void _dir_fill_wild(char *dst, uint8_t len) {
    uint8_t i;
    for (i = 0; i < len; ++i)
        dst[i] = '?';
}

static int _dir_parse_pattern(const char *path, _fcb_t *fcb) {
    uint8_t i;
    uint8_t j;
    char c;
    char drive;

    memset(fcb, 0, sizeof(*fcb));
    _dir_fill_wild(fcb->filename, 8);
    _dir_fill_wild(fcb->filetype, 3);

    drive = 'A' + bdos(DRV_GET, 0);
    fcb->drive = (uint8_t)(drive - 'A' + 1);

    if (path == NULL || *path == '\0')
        return 0;

    i = 0;
    c = toupper(path[i]) & 0x7f;
    if (c >= 'A' && c <= 'P' && path[i + 1] == ':') {
        fcb->drive = (uint8_t)(c - 'A' + 1);
        i += 2;
    }

    if (path[i] == '\0')
        return 0;

    if (path[i] == '[')
        return -1;

    for (j = 0; j < 8 && path[i] != '\0' && path[i] != '.' && path[i] != '['; ++i) {
        c = toupper(path[i]) & 0x7f;
        if (c == '*') {
            while (j < 8)
                fcb->filename[j++] = '?';
            ++i;
            break;
        }
        if (c == '?' || isalpha(c) || isdigit(c) || c == '_' || c == '$') {
            fcb->filename[j++] = c;
            continue;
        }
        return -1;
    }

    if (path[i] == '.') {
        ++i;
        for (j = 0; j < 3 && path[i] != '\0' && path[i] != '['; ++i) {
            c = toupper(path[i]) & 0x7f;
            if (c == '*') {
                while (j < 3)
                    fcb->filetype[j++] = '?';
                ++i;
                break;
            }
            if (c == '?' || isalpha(c) || isdigit(c) || c == '_' || c == '$') {
                fcb->filetype[j++] = c;
                continue;
            }
            return -1;
        }
    }

    return path[i] == '\0' ? 0 : -1;
}

static void _dir_copy_name(char *dst, const uint8_t *src) {
    uint8_t i;
    uint8_t out = 0;

    for (i = 0; i < 8; ++i) {
        if (src[i] == ' ')
            break;
        dst[out++] = (char)(src[i] & 0x7f);
    }

    if (src[8] != ' ' || src[9] != ' ' || src[10] != ' ') {
        dst[out++] = '.';
        for (i = 8; i < 11; ++i) {
            if (src[i] == ' ')
                break;
            dst[out++] = (char)(src[i] & 0x7f);
        }
    }

    dst[out] = '\0';
}

static struct dirent *_dir_search(_dir_t *dir, uint8_t fn) {
    bdos_ret_t result;
    uint8_t *dent;

    bdos(F_DMAOFF, (uint16_t)&dir->dma[0]);
    bdosret(fn, (uint16_t)&dir->fcb, &result);
    if (result.reta == BDOS_FAILURE)
        return NULL;

    dent = &dir->dma[(result.reta & 0x03) * 32];
    dir->entry.d_type = dent[0];
    _dir_copy_name(dir->entry.d_name, &dent[1]);
    return &dir->entry;
}

DIR *opendir(const char *path) {
    _dir_t *dir;

    dir = (_dir_t *)calloc(1, sizeof(*dir));
    if (dir == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    if (_dir_parse_pattern(path, &dir->fcb) != 0) {
        free(dir);
        errno = EINVAL;
        return NULL;
    }

    errno = 0;
    return (DIR *)dir;
}

int closedir(DIR *dp) {
    if (dp == NULL) {
        errno = EINVAL;
        return -1;
    }

    free(dp);
    errno = 0;
    return 0;
}

struct dirent *readdir(DIR *dp) {
    _dir_t *dir;

    if (dp == NULL) {
        errno = EINVAL;
        return NULL;
    }

    dir = (_dir_t *)dp;
    if (dir->entry.d_name[0] == '\0')
        return _dir_search(dir, F_SEARCHFIRST);

    return _dir_search(dir, F_SEARCHNEXT);
}
