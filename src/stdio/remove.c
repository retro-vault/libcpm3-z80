/*
 * remove.c
 *
 * Delete a named file from the CP/M filesystem via BDOS F_DELETE.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/bdos.h>
#include <file/_fcb.h>

int remove(const char *path)
{
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    char drive[2];
    int user;
    _fcb_t fcb;
    bdos_ret_t result;

    if (_splitpath(path, drive, &user, fname, ext) < 0) {
        errno = ENOENT;
        return -1;
    }

    memset(&fcb, 0, sizeof(fcb));
    _to_fcb_name(fcb.filename, fname, MAX_FNAME);
    _to_fcb_name(fcb.filetype, ext, MAX_EXT);
    fcb.drive = (uint8_t)(drive[0] - 'A' + 1);

    bdosret(F_DELETE, (uint16_t)&fcb, &result);
    if (result.reta == BDOS_FAILURE) {
        errno = EIO;
        return -1;
    }

    errno = 0;
    return 0;
}
