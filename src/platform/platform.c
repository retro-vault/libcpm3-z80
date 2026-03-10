/*
 * platform.c
 *
 * Default platform implementations of msleep()
 * and _libinit(). Only compiled when PLATFORM_NONE
 * is defined (i.e. make PLATFORM=none, the default).
 *
 * For any other platform these symbols are left undefined so
 * the linker will report unresolved externals -- link your own
 * implementations before this library to satisfy them.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <platform.h>

/* Internal 1 ms busy-wait for the 4 MHz Z80 (see _delay.s). */
extern void _delay_1ms(void);

#ifdef PLATFORM_NONE

/* msleep(int millisec)
 *
 * Busy-wait delay for the given number of milliseconds.  Built on
 * _delay_1ms(), which is cycle-counted to exactly 4000 T-states (1 ms)
 * on a 4 MHz Z80.  The C loop itself adds ~30-50 uncounted T-states per
 * iteration, so long delays accumulate a small positive error (~0.1-0.2 ms
 * per 100 ms).  Acceptable for coarse timing; for tight timing call
 * _delay_1ms() directly from assembly.
 */
void msleep(int millisec) {
    /* Each call to _delay_1ms() is accurate to 4000 T-states (1 ms at
       4 MHz). However the C loop overhead -- decrement, branch, call
       setup -- adds roughly 30-50 extra T-states per iteration that are
       not accounted for inside _delay_1ms. The error accumulates: a
       100 ms delay may run ~0.1-0.2 ms long. For coarse delays this is
       acceptable; for tight timing use _delay_1ms() directly in asm. */
    while (millisec-- > 0)
        _delay_1ms();
}

void _libinit(void) {
    /* Identify the platform. */
    libplatform = PLATFORM_NAME_STR;

    /* CP/M 3 console expects CR+LF for newlines. */
    nltype = NL_CRLF;
}

#endif /* PLATFORM_NONE */
