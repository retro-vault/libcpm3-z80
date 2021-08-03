/*
 * init.c
 *
 * Standard C library initialization.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 03.08.2012   tstih
 *
 */
#include <util/mem.h>

void _stdlib_init() {
    /* ininitalize memory */
    _memory_init();
}