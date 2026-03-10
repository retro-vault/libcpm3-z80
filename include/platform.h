/*
 * platform.h
 *
 * Non-standard CP/M 3 Z80 platform extensions.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 10.03.2026   tstih
 *
 */
#ifndef LIBCPM3_PLATFORM_H
#define LIBCPM3_PLATFORM_H

/* Expand PLATFORM_NAME (a bare token from -DPLATFORM_NAME=...) into a
 * C string literal. The two-level indirection forces macro expansion
 * of PLATFORM_NAME before stringification (#), so PLATFORM_NAME_STR
 * yields e.g. "none" or "partner" not the literal text "PLATFORM_NAME". */
#define _PLATFORM_TOSTR(x)  #x
#define _PLATFORM_STR(x)    _PLATFORM_TOSTR(x)
#define PLATFORM_NAME_STR   _PLATFORM_STR(PLATFORM_NAME)

/* Newline translation mode for console output.
 * Controls how '\n' is expanded when writing to stdout/stderr. */
#define NL_LF       0   /* emit '\n' as-is */
#define NL_CRLF     1   /* emit '\n' as '\r\n' */
#define NL_LFCR     2   /* emit '\n' as '\n\r' */

/* Current newline translation mode.
 * Initialized to NL_LF; set to NL_CRLF by _libinit() on CP/M 3. */
extern char nltype;

/* Name of the platform the library was built for (e.g. "none").
 * Set by _libinit() to the value of PLATFORM_NAME_STR. NULL until then. */
extern const char *libplatform;

/* Name of the running program.
 * CP/M does not pass argv[0] to the application, so this is NULL by
 * default.  Set it explicitly in your own startup code or Makefile-driven
 * init to give the program a meaningful name. */
extern const char *progname;

/* Busy-wait delay.
 * Pauses execution for the given number of milliseconds.
 * Accuracy depends on the platform implementation. */
extern void msleep(int millisec);

/* Platform initializer hook.
 * Called once by the standard library startup code (_stdlib_init).
 * Provide your own implementation when PLATFORM != none. */
extern void _libinit(void);

#endif /* LIBCPM3_PLATFORM_H */
