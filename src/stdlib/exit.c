/*
 * exit.c
 *
 * Terminate the program, running atexit handlers before calling _exit().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

extern void _exit(int status);
#define ATEXIT_MAX 8
extern void (*__atexit_funcs[ATEXIT_MAX])(void);
extern unsigned char __atexit_count;

void exit(int status) {
    while (__atexit_count > 0) {
        --__atexit_count;
        __atexit_funcs[__atexit_count]();
    }
    _exit(status);
}
