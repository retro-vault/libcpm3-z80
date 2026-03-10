/*
 * _memtop.c
 *
 * Return the top address of allocatable memory under CP/M 3.
 * Reads the BDOS entry address at 0x0006 to find the TPA boundary.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_mem.h"

/* On CP/M, address 0x0005 is a JP instruction to BDOS.
   The 16-bit destination address at 0x0006 is the BDOS entry
   point, which marks the top of usable TPA memory. */
size_t _memtop(void) {
    return *(size_t *)0x0006;
}
