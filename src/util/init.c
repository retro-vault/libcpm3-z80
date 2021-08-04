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
#include <util/cmdline.h>
#include <util/mem.h>

void _stdlib_init() {

    /* initialize comamnd line args */
    _init_cmdline();

    /* ininitalize memory management */
    _memory_init();
}