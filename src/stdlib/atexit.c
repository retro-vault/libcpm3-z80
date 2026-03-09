/*
 * atexit.c
 *
 * Register a function to be called when exit() runs.
 * Up to ATEXIT_MAX (8) handlers may be registered.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

#define ATEXIT_MAX 8

void (*__atexit_funcs[ATEXIT_MAX])(void);
unsigned char __atexit_count = 0;

int atexit(void (*func)(void)) {
    if (__atexit_count >= ATEXIT_MAX)
        return -1;
    __atexit_funcs[__atexit_count++] = func;
    return 0;
}
