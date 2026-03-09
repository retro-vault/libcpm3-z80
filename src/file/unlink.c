/*
 * unlink.c
 *
 * Delete a named file from the CP/M filesystem via remove().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <unistd.h>
#include <stdio.h>

int unlink(const char *path) {
    return remove(path);
}
