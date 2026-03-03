/*
 * memtop.c
 *
 * Return top of available memory (start of BDOS).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 17.02.2026   tstih
 *
 */
#include <mem/mem.h>

/* On CP/M, address 0x0005 is a JP instruction to BDOS.
   The 16-bit destination address at 0x0006 is the BDOS entry
   point, which marks the top of usable TPA memory. */
size_t _memtop(void) {
    return *(size_t *)0x0006;
}
