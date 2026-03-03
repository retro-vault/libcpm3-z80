/*
 * libinit.c
 *
 * Library initialization hook and platform identifier.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 17.02.2026   tstih
 *
 */

/* Platform identifier string. */
char *libplatform = "z80-cpm3";

/* Called at the end of _stdlib_init(). Override in your application
   to perform platform-specific initialization after the C runtime
   (heap, file descriptors, command line) has been set up. */
void libinit(void) {}
