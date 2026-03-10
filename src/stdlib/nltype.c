/*
 * nltype.c
 *
 * Define the newline translation mode variable used by console output.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

/* Newline translation mode (set per-platform in _libinit). */
char nltype = NL_LF;

/* Platform name string (set in _libinit to PLATFORM_NAME_STR). */
const char *libplatform = NULL;

/* Running program name for argv[0] (set in _libinit if needed). */
const char *progname = NULL;
