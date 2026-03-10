/*
 * _stdlib_init.c
 *
 * Initialize standard-library subsystems at program startup:
 * command line, heap, file descriptors, and the platform hook.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <platform.h>
#include <file/_fd.h>

#include "_cmdline.h"
#include "_mem.h"

void _stdlib_init(void) {
    /* Initialize comamnd line args. */
    _init_cmdline();

    /* Ininitalize memory management. */
    _memory_init();

    /* Initialize file descriptors. */
    _init_fds();

    /* Finalize initialization, call the hook. */
    _libinit();
}
