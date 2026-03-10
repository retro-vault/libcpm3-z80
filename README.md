![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url] [![license.badge]][license.url]

# Standard C library for CP/M 3 Z80

## Table of contents

- [Introduction](#introduction)
- [Building the Library](#building-the-library)
- [Compiling your CP/M program](#compiling-your-cpm-program)
- [Running the Tests](#running-the-tests)
- [Platform-dependent Functions](#platform-dependent-functions)
- [Source Tree Layout](#source-tree-layout)
- [What is implemented?](#what-is-implemented-)
- [Standard C headers with working implementations](#standard-c-headers-with-working-implementations)
- [Standard C interfaces still missing from the provided partial headers](#standard-c-interfaces-still-missing-from-the-provided-partial-headers)
- [Standard C headers not currently provided](#standard-c-headers-not-currently-provided)
- [POSIX / Unix-style extensions](#posix--unix-style-extensions)
- [POSIX pieces still missing](#posix-pieces-still-missing)
- [Non-standard libcpm3-z80 extensions](#non-standard-libcpm3-z80-extensions)
- [To Do](#to-do)

## Introduction

**libcpm3-z80** is a **portable**, **readable**, and **minimal** [ISO/IEC 9899:TC2](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) *Standard C Library* for Digital Research's CP/M 3.

Implementing a standard library shouldn't be a daunting task. Unless the library immoderately aspires to target all architectures and all compilers by using sophisticated preprocessor directives and tricks, 
only known to god and a few earthlings.

**libcpm3-z80** is an attempt to provide a library, written in purest *C*, with a clear separation of platform independent and platform dependent code. To port it to your architecture you need to provide a handful of well documented platform specific functions that the standard requires and are not available in *CP/M*'s *BDOS*.

The library is now organized directly by public subsystem under `src/`:
`stdlib/`, `stdio/`, `string/`, `sys/`, `platform/`, `setjmp/`, and so on.
There is no longer a separate `src/_impl/` tree.


## Building the library

Clone the repository first:

```sh
git clone https://github.com/tstih/libcpm3-z80.git
cd libcpm3-z80
```

### Commands

| Command | Description |
|---------|-------------|
| `make` | Build the library |
| `make test` | Build library + tests and run them in the CP/M emulator |
| `make clean` | Remove `build/` and `bin/` |

### Parameters

| Parameter | Values | Default | Description |
|-----------|--------|---------|-------------|
| `DOCKER` | `on`, `off` | `on` | `on` builds inside the `wischner/sdcc-z80` Docker image, no local SDCC needed. `off` builds natively and requires SDCC on `PATH`. |
| `PLATFORM` | name | `none` | Defines `PLATFORM_<NAME>` for conditional platform code. The default platform provides implementations of `msleep()` and `_libinit()`. Any other value omits them — link your own. |
| `BUILD_DIR` | path | `build/` | Intermediate build products (`.rel`, archive). |
| `BIN_DIR` | path | `bin/` | Final outputs: library, CRT0, headers. |

Examples:

```sh
make                          # build inside Docker (default)
make DOCKER=off               # build natively with local SDCC
make PLATFORM=myboard         # custom platform, no no-op stubs
make DOCKER=off BUILD_DIR=out/build BIN_DIR=out/bin
```

> **Warning:** `make test` requires `DOCKER=on`. With `DOCKER=off` the test
> binaries will be built but cannot be run — `make test` will error out.

### Output files

All outputs are placed in `bin/` (or `BIN_DIR` if overridden):

| File | Description |
|------|-------------|
| `crt0cpm3-z80.rel` | C runtime start-up object (must be linked first) |
| `libcpm3-z80.lib`  | CP/M 3 standard C library archive |
| `include/`         | Public header files |

`libsdcc-z80.lib` (SDCC integer/float stubs) is downloaded automatically to
`lib/` on the first `make test` and must also be linked with your program.

> **Urgent:** `libcpm3-z80.lib` alone is not enough. Any program using this
> library must also link `lib/libsdcc-z80.lib`, or the final link will be
> incomplete. Repository: https://github.com/retro-vault/libsdcc-z80

### SDCC calling convention

The library targets SDCC Z80 `__sdcccall(1)`. You need SDCC version >= 4.2.0.

## Compiling your CP/M program

You need SDCC installed locally, or you can adapt the Docker invocation from
the `test/Makefile` as a template. The link order is fixed: CRT0 first,
your object files, then the library, then the SDCC stubs last.

> **Urgent:** Always link `lib/libsdcc-z80.lib` together with
> `bin/libcpm3-z80.lib`. The SDCC support library is required and lives here:
> https://github.com/retro-vault/libsdcc-z80

If you use upstream `sdcc` directly, add `-mz80` on both the compile and
link commands. Also set the code and data locations explicitly when linking:
CP/M `.COM` programs must start at `0x100`, and plain upstream SDCC otherwise
tries to place the data segment at `0x8000`. The custom Docker toolchain used
in this project already defaults to Z80, so the examples there do not need
`-mz80` explicitly.

```sh
# Compile
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
     -I bin/include -c -o myprog.rel myprog.c

# Link
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
     --code-loc 0x100 --data-loc 0 \
     -o myprog.ihx \
     bin/crt0cpm3-z80.rel myprog.rel \
     bin/libcpm3-z80.lib lib/libsdcc-z80.lib

# Convert IHX to CP/M .COM (binary starts at 0x0100)
sdobjcopy -I ihex -O binary myprog.ihx myprog.com
```

With the project's Docker SDCC wrapper, the target selection is already baked
in, but `--code-loc 0x100 --data-loc 0` still applies if you invoke upstream
`sdcc` yourself.

See `test/Makefile` for a complete working example.

## Running the tests

```sh
make test
```

This builds the library and all test `.com` binaries inside Docker, then runs
them automatically inside a RunCPM CP/M 3 emulator container. Results are
written to `bin/<name>.txt`.

> **Note:** `make test` requires Docker (`DOCKER=on`, the default). With
> `DOCKER=off` only the test binaries are compiled — they cannot be run
> without the CP/M emulator.

The test suite comprises:

| Binary | Tests |
|--------|-------|
| `tctype.com`   | `ctype.h` character classification |
| `tstring.com`  | `string.h` string functions |
| `tstdlib.com`  | `stdlib.h` general utilities |
| `tstdio.com`   | `stdio.h` file I/O |
| `ttime.com`    | `time.h` time functions |
| `tmath.com`    | `math.h` floating-point math |
| `tmem.com`     | allocator internals and utility lists |
| `tfile.com`    | low-level file API (`open/read/write/lseek/stat`) |
| `tsdcc.com`    | SDCC runtime integration |
| `tsetjmp.com`  | `setjmp`/`longjmp` |

Each program prints `PASS` or `FAIL` per test case and a summary line at the
end. You can also copy any `.com` file to a real CP/M disk and run it on
hardware or an emulator such as [z80pack](https://www.autometer.de/unix4fun/z80pack/).

## Source Tree Layout

Implementation files are grouped by the public library area they support:

| Folder | Contents |
|--------|----------|
| `src/sys/` | CP/M system bindings such as `bdos.s` and `crt0cpm3-z80.s` |
| `src/stdlib/` | `stdlib` implementation plus allocator, list, and startup internals |
| `src/stdio/` | `stdio` implementation plus internal formatting helpers |
| `src/platform/` | platform-specific hooks and timing helpers |
| `src/setjmp/` | `setjmp` / `longjmp` |
| `src/string/`, `src/time/`, `src/math/`, `src/file/`, ... | subsystem implementations |

The old `src/_impl/` layout has been retired.

## Platform-dependent functions

### The PLATFORM system

The library is designed to be portable. Everything that depends on specific
hardware is isolated behind a single `PLATFORM` make parameter. The value is
just a short build-time name for your target-specific support code:

| Example | Meaning |
|---------|---------|
| `none` | Built-in default platform (the default) |
| `partner` | Iskra Delta Partner with your own `platform.c` |
| `myboard` | Any custom target with your own platform support |

The name is not parsed or validated by the build system. Choose something
short and descriptive so that `libplatform` is meaningful at runtime.

```sh
make PLATFORM=none      # built-in default
make PLATFORM=partner   # your own Partner platform.c
make PLATFORM=myboard   # any custom platform
```

At build time this defines two preprocessor macros:

| Macro | Example value | Purpose |
|-------|--------------|---------|
| `PLATFORM_NONE` | (defined/not defined) | Guards the built-in default platform code |
| `PLATFORM_NAME` | `none` | Bare token of the platform name |
| `PLATFORM_NAME_STR` | `"none"` | String literal, derived via `#` stringification in `platform.h` |

### Platform header

All platform-specific symbols are declared in `platform.h`. Include it in any
file that uses `nltype`, `libplatform`, `progname`, or `msleep()`:

```c
#include <platform.h>
```

### Platform variables

| Variable | Type | Default | Description |
|----------|------|---------|-------------|
| `libplatform` | `const char *` | `NULL` | Platform name string; set to `PLATFORM_NAME_STR` by `_libinit()` |
| `nltype` | `char` | `NL_LF` | Newline translation mode for all console output |
| `progname` | `const char *` | `NULL` | Program name; CP/M does not pass `argv[0]`, so set this explicitly in your own startup code if you need it |

`nltype` controls how `\n` is expanded by all output functions (`putchar`,
`printf`, `fwrite`, etc.):

| Value | Constant | Console output |
|-------|----------|---------------|
| `0` | `NL_LF` | `\n` only (Unix style) |
| `1` | `NL_CRLF` | `\r\n` (CP/M / DOS style, **default for the built-in platform**) |
| `2` | `NL_LFCR` | `\n\r` |

### Platform functions

Two functions have no CP/M 3 BDOS equivalent and must be provided per platform:

| Function | Signature | Description |
|----------|-----------|-------------|
| `msleep()` | `void msleep(int millisec)` | Busy-wait delay in milliseconds |
| `_libinit()` | `void _libinit(void)` | Platform initializer, called once at startup |

Both are declared in `platform.h`.

`_libinit()` is called at the very end of C runtime initialization — after the
heap, file descriptors, and command-line arguments are ready. Use it to set
platform variables and do any hardware-specific startup.

The default `none` platform implements both:

```c
void _libinit(void) {
    libplatform = PLATFORM_NAME_STR;  /* "none"            */
    nltype      = NL_CRLF;           /* CP/M needs CR+LF  */
}
```

```c
void msleep(int millisec) {
    /* Calls _delay_1ms() once per millisecond.
       _delay_1ms() is a Z80 assembly routine that burns
       exactly 4000 T-states (= 1 ms) on a 4 MHz CPU.

       T-state budget:
         Static:  CALL=17  RET=10  LD B,n=7  final DJNZ=8  => 42
         Dynamic: 209 × DEC HL(6) + 208 × DJNZ(13)         => 3958
         Total:   4000 T-states = 1 ms at 4 MHz

       Note: the C loop itself adds ~30-50 uncounted T-states per
       iteration. Long delays accumulate a small positive error
       (~0.1-0.2 ms per 100 ms). For tight timing call _delay_1ms()
       directly from assembly.                               */
    while (millisec-- > 0)
        _delay_1ms();
}
```

### Providing your own platform

If you pass a `PLATFORM` other than `none` the library does **not**
include `msleep()` or `_libinit()`. You get unresolved externals at link time
until you supply your own implementations. Link your object file before the
library:

```sh
sdcc ... myprog.rel myplatform.rel bin/libcpm3-z80.lib ...
```

Inside your `_libinit()` set `libplatform` and `nltype` as appropriate for
your hardware. Set `progname` only if your startup environment provides a
program name:

```c
#include <platform.h>

void _libinit(void) {
    libplatform = PLATFORM_NAME_STR;  /* set by the build system */
    nltype      = NL_CRLF;           /* or NL_LF, NL_LFCR      */
}
```

## What is implemented?

This library currently provides a small, test-backed subset of the C library,
plus a CP/M-oriented POSIX-like layer and a few CP/M-specific extensions.

### Standard C headers with working implementations

These headers are present and backed by code in `src/`:

| Header | Status | Implemented surface |
|--------|--------|---------------------|
| `ctype.h` | partial | `isalnum`, `isalpha`, `iscntrl`, `isdigit`, `isgraph`, `islower`, `isprint`, `ispunct`, `isspace`, `isupper`, `isxdigit`, `tolower`, `toupper` |
| `assert.h` | implemented | `assert()` macro with `NDEBUG` support |
| `errno.h` | partial | `errno` plus a small CP/M-oriented error set |
| `float.h` | partial | single-precision constants only |
| `inttypes.h` | partial | `intmax_t`, `uintmax_t`, `PRI*` macros, `strtoimax`, `strtoumax` |
| `iso646.h` | implemented | alternative operator spellings |
| `limits.h` | partial | integer and size limits for this target |
| `math.h` | partial | `ceil`, `cos`, `cot`, `exp`, `fabs`, `floor`, `frexp`, `ldexp`, `log`, `log10`, `modf`, `pow`, `sin`, `sqrt`, `tan` |
| `setjmp.h` | implemented | `setjmp`, `longjmp` |
| `stdarg.h` | implemented | `va_list`, `va_start`, `va_arg`, `va_end` |
| `stdbool.h` | implemented | `bool`, `true`, `false` macros |
| `stddef.h` | partial | `size_t`, `ptrdiff_t` |
| `stdint.h` | partial | fixed-width 8/16/32-bit integer types |
| `stdio.h` | partial | `FILE`, `stdin`, `stdout`, `stderr`, `fopen`, `fclose`, `fflush`, `fgetc`, `fgets`, `fputc`, `fputs`, `fread`, `fseek`, `ftell`, `fwrite`, `feof`, `ferror`, `clearerr`, `getc`, `getc_unlocked`, `getchar`, `gets`, `getw`, `fprintf`, `perror`, `printf`, `putc`, `putchar`, `puts`, `remove`, `rewind`, `setbuf`, `setvbuf`, `sprintf`, `tmpfile`, `tmpnam`, `ungetc`, `vfprintf`, `vprintf`, `vsprintf` |
| `stdnoreturn.h` | implemented | `noreturn` macro |
| `stdlib.h` | partial | `abort`, `atexit`, `exit`, `abs`, `atof`, `atoi`, `atol`, `bsearch`, `div`, `itoa`, `labs`, `ldiv`, `rand`, `srand`, `strtol`, `strtoul`, `malloc`, `calloc`, `free`, `qsort` |
| `string.h` | partial | `memchr`, `memcmp`, `memcpy`, `memset`, `strchr`, `strcmp`, `strcpy`, `strcspn`, `strlen`, `strncmp`, `strncpy`, `strrchr`, `strsep`, `strerror`, `strrev`, `strtok`, `stolower`, `stoupper` |
| `time.h` | partial | `asctime`, `clock`, `ctime`, `difftime`, `gmtime`, `mktime`, `time` |

### Standard C interfaces still missing from the provided partial headers

All currently declared public interfaces are backed by code, but many headers
are intentionally only a subset of the full ISO C surface. The main gaps are:

| Header | Not yet provided |
|--------|---------------------|
| `math.h` | most of the wider C math surface beyond the current single-precision core |
| `stdio.h` | `fscanf`, `rename`, `scanf`, `sscanf` |
| `stdlib.h` | `getenv`, `system` |
| `time.h` | `strftime` and timezone/DST extensions beyond UTC-style operation |

### Standard C headers not currently provided

This is not yet a full hosted C library. In particular, these standard headers
are not shipped here:

- `complex.h`
- `fenv.h`
- `locale.h`
- `signal.h`
- `stdalign.h`
- `stdatomic.h`
- `tgmath.h`
- `threads.h`
- `uchar.h`
- `wchar.h`
- `wctype.h`

### POSIX / Unix-style extensions

These are not part of ISO C. They are grouped separately because they form the
library's Unix-like I/O layer on top of CP/M 3:

| Header | Status | Implemented surface |
|--------|--------|---------------------|
| `fcntl.h` | partial | `open`, `creat`, `O_*`, `SEEK_*` |
| `sys/types.h` | partial | `ssize_t`, `off_t` |
| `sys/stat.h` | partial | `struct stat`, `stat` |
| `unistd.h` | partial | `read`, `write`, `close`, `fsync`, `lseek`, `unlink` |
| `dirent.h` | partial | `DIR`, `struct dirent`, `opendir`, `readdir`, `closedir` using CP/M wildcard search (`A:*.COM`, `*.TXT`, etc.) |

### POSIX pieces still missing

The POSIX layer is intentionally small. Common Unix interfaces not currently
provided include:

- `access`
- `dup`, `dup2`
- `isatty`
- `mkdir`, `rmdir`
- `pipe`
- `rename` as a POSIX filesystem call
- `stat` variants such as `fstat`
- process APIs such as `exec*`, `fork`, `wait`

### Non-standard libcpm3-z80 extensions

These are project-specific or CP/M-specific APIs rather than ISO C or POSIX:

| Header | Extension |
|--------|-----------|
| `platform.h` | `nltype`, `NL_LF/NL_CRLF/NL_LFCR`, `libplatform`, `progname`, `msleep()`, `_libinit()` |
| `sys/bdos.h` | `bdos()`, `bdosret()`, CP/M 3 BDOS constants, `bdos_ret_t` |
| `time.h` | `gettimeofday()`, `settimeofday()`, `struct timeval` |
| `stdlib.h` | `_splitpath()` |
| `string.h` | `stoupper()`, `stolower()`, `strrev()` |


## To Do

- Expand standard-header coverage if the project goal moves beyond the current
  minimal subset.

[language.url]:   https://en.wikipedia.org/wiki/ANSI_C
[language.badge]: https://img.shields.io/badge/language-C-blue.svg

[standard.url]:   https://en.wikipedia.org/wiki/C89/
[standard.badge]: https://img.shields.io/badge/standard-C89-blue.svg

[license.url]:    https://github.com/tstih/libcpm3-z80/blob/main/LICENSE
[license.badge]:  https://img.shields.io/badge/license-MIT-blue.svg

[status.badge]:  https://img.shields.io/badge/status-stable-dkgreen.svg
