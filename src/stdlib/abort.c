/*
 * abort.c
 *
 * Terminate the program abnormally without returning to the caller.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

void abort(void) {
    exit(1);
}
