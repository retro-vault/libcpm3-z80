/*
 * setjmp.h
 *
 * Non-local jump support.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#ifndef LIBCPM3_SETJMP_H
#define LIBCPM3_SETJMP_H

#include <stdint.h>

/* Saved register set: IX, return PC, caller SP. */
typedef uint16_t jmp_buf[3];

/* Save execution context. */
extern int setjmp(jmp_buf env);

/* Restore execution context. */
extern void longjmp(jmp_buf env, int val);

#endif /* LIBCPM3_SETJMP_H */
