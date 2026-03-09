![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url] [![license.badge]][license.url]

# Standard C library for CP/M 3 Z80

## Table of contents

- [Introduction](#introduction)
- [Building the Library](#building-the-library)
- [Compiling your CP/M program](#compiling-your-cpm-program)
- [Running the Tests](#running-the-tests)
- [Platform-dependent Functions](#platform-dependent-functions)
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


## Building the library

Clone the repository first:

```sh
git clone https://github.com/tstih/libcpm3-z80.git
cd libcpm3-z80
```

### Quick start (Docker, recommended)

Bare `make` builds the library inside the `wischner/sdcc-z80` Docker image —
no local SDCC installation required:

```sh
make
```

### Build targets

| Target | Description |
|--------|-------------|
| `make` | Build library inside Docker (default) |
| `make test` | Build library + tests inside Docker, run tests in CP/M emulator |
| `make native` | Build library natively (requires SDCC on PATH; no tests) |
| `make deps` | Download `libsdcc-z80` runtime helpers to `lib/` (run once before `make test`) |
| `make install` | Install library and headers to `DESTDIR$(PREFIX)` |
| `make clean` | Remove build artifacts from `build/` and `bin/` |
| `make docker-clean` | Remove artifacts via Docker (handles root-owned files from old builds) |
| `make docker-test-rebuild` | Force-rebuild the CP/M emulator Docker image |

> **Note:** `make native` builds the library only. There is no native test
> target — tests require the CP/M emulator Docker image.

### Output files

All outputs are placed in `bin/`:

| File | Description |
|------|-------------|
| `crt0cpm3-z80.rel` | C runtime start-up object (must be linked first) |
| `libcpm3-z80.lib`  | CP/M 3 standard C library archive |
| `include/`         | Public header files |

`libsdcc-z80.lib` (SDCC integer/float stubs) is placed in `lib/` by
`make deps` and must also be linked with your program.

### Overriding output directories

The top-level Makefile supports overriding:

- `BUILD_DIR`: intermediate `.rel`, `.ihx`, and archive build products
- `BIN_DIR`: final outputs copied for consumption (`.lib`, `.rel`, headers)

This is useful when `libcpm3-z80` is a sub-project and you want its artifacts
placed into your own project's output tree:

```sh
make native \
  BUILD_DIR="$PWD/out/libcpm3/build" \
  BIN_DIR="$PWD/out/libcpm3/bin"
```

Or when using `make -C` from a parent project:

```sh
make -C third_party/libcpm3-z80 native \
  BUILD_DIR="$PWD/build/libcpm3" \
  BIN_DIR="$PWD/toolchain/cpm3"
```

### Cleaning up

```sh
make clean          # remove build/ and bin/
make docker-clean   # same, but via Docker (for root-owned artifacts)
```

## Compiling your CP/M program

You need SDCC installed locally, or you can adapt the Docker invocation from
the `test/Makefile` as a template. The link order is fixed: CRT0 first,
your object files, then the library, then the SDCC stubs last.

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

Download the SDCC runtime helpers first (needed to link test binaries):

```sh
make deps
```

Then build and run all tests in the CP/M emulator with a single command:

```sh
make test
```

This builds the library and all test `.com` binaries inside Docker, then runs
them automatically inside a RunCPM CP/M 3 emulator container. Results are
written to `bin/<name>.txt`.

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

## Platform-dependent functions

Two functions have no CP/M 3 BDOS equivalent and ship as no-ops:

| Function | Declared in | Default implementation |
|----------|-------------|------------------------|
| `msleep()`  | `unistd.h` | no-op — CP/M 3 has no timer |
| `libinit()` | `stdlib.h` | no-op — user startup hook  |

To override any of these, define the function in your own source file and link
it **before** the library. The linker resolves the first definition it finds,
so your version takes precedence over the one in the archive.

`libinit()` is called at the end of C runtime initialization (after the heap,
file descriptors, and command-line arguments are set up). Use it for any
platform-specific startup code.

There is also one platform-dependent variable: `progname` (`stdlib.h`).
Set it inside `libinit()` to populate `argv[0]`; otherwise `argv[0]` is an
empty string. All other command-line arguments are parsed from the CP/M
program tail automatically.

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
| `sys/bdos.h` | `bdos()`, `bdosret()`, CP/M 3 BDOS constants, `bdos_ret_t` |
| `time.h` | `gettimeofday()`, `settimeofday()`, `struct timeval` |
| `stdlib.h` | `libplatform`, `progname`, `nltype`, `_libinit()`, `_splitpath()` |
| `string.h` | `stoupper()`, `stolower()`, `strrev()` |
| `unistd.h` | `_msleep()` placeholder hook |


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
