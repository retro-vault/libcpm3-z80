/*
 * stdstreams.c
 *
 * Define the stdin, stdout, and stderr stream objects.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

static FILE _stdin_obj  = { "r", 0, false, false, -1 };
static FILE _stdout_obj = { "w", 1, false, false, -1 };
static FILE _stderr_obj = { "w", 2, false, false, -1 };

FILE *stdin  = &_stdin_obj;
FILE *stdout = &_stdout_obj;
FILE *stderr = &_stderr_obj;
