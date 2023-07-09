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
#include <mem/mem.h>
#include <file/fd.h>

void _stdlib_init(void) {
    /* Initialize comamnd line args. */
    _init_cmdline();

    /* Ininitalize memory management. */
    _memory_init();

    /* Initialize file descriptors. */
    _init_fds();

    /* Finalize initialization, call the hook. */
    libinit();
}
