/*
 * stdstreams.c
 *
 * Definitions of standard stream objects.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

static FILE _stdin_obj  = { "r", 0, false };
static FILE _stdout_obj = { "w", 1, false };
static FILE _stderr_obj = { "w", 2, false };

FILE *stdin  = &_stdin_obj;
FILE *stdout = &_stdout_obj;
FILE *stderr = &_stderr_obj;
