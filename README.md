# libcpm3-z80

**libcpm3-z80** is a **portable**, **readable**, and **minimal** [ISO/IEC 9899:TC2](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) *Standard C Library* for Digital Research's CP/M 3.

Implementing a standard library shouldn't be a daunting task. Unless the library immoderately aspires to target all architectures and all compilers by using sophisticated preprocessor directives and tricks, 
only known to god and a few earthlings.

**libcpm3-z80** is an attempt to provide a library, written in purest C, with a clear separation of platform independent and platform dependent code. To port it to your architecture you need to provide a handful of well documented platform specific functions that the standard requires and are not available in CP/M's BDOS.

# Compiling the libcpm3-z80

You need a Linux with the **latest** version of SDCC development tools intalled.

Then get the repository by executing 

`git clone https://github.com/tstih/libcpm3-z80.git --recurse-submodules`

This will download **libcpm3-z80** and submodule [libsdcc-z80](https://github.com/tstih/libsdcc-z80). 

After that you can compile a basic version of **libcpm3-z80** by issuing a `make` command in root folder.

Make will produce three files in the `bin` folder.
 * `crt0cpm3-z80.rel` This is the C runtime start-up file.
 * `libcpm3-z80.lib` This is the CP/M 3 standard C library.
 * `libsdcc-z80.lib` This is the SDCC bare metal library.

You need to link all three with your CP/M program.

# Compiling my program

Create a sample program `hello.c`.

~~~cpp
#include <stdio.h>

void main(int argc, char *argv[]) {
    if (argc==2)
        printf("Hello %s!\n",argv[1]);
    else
        printf("Hello world!\n");
}
~~~

Set the `LC3DIR` variable to point to your **libcpm3-z80** rot directory, or simmply replace it in following commands.

Compile your program.

~~~
sdcc -o hello.rel \
    -c --std-c11 -mz80 --debug \
    --nostdinc --no-std-crt0 --nostdinc --nostdlib \
    -I$(LC3DIR)/include \
    hello.c
~~~

Link it to address `0x100`.

~~~
sdcc -o hello.ihx \
    -mz80 -Wl -y --code-loc 0x100 --data-loc 0x200 \
    --no-std-crt0 --nostdinc --nostdlib \
    -L$(LC3DIR)/bin -llibsdcc-z80 -llibcpm3-z80 \
    crt0cpm-z80.rel hello.rel
~~~

And, finally, create a *CP/M* `hello.com` file.

~~~

~~~

# Advanced libcpm3-z80 features

The library was designed for *CP/M 3*, and uses *BDOS* system calls to implement most features. But some are not covered by the *BDOS*. An example is reading and writing system time. The library still implements almost complete `time.h`. By providing your own platform dependant functions you can unlock full features of the **libcpm3-z80**.

To compile the platform dependant library add your platform name to the arguments. 

~~~
make PLATFORM=iskra-delta-partner
~~~

The name can be anything since the source code just checks if the variable `PLATFORM` is not zero. The system will then ignore the existing basic *(proxy!)* platform dependant code and expect that the missing functions are found at link time in another library or object file.

 > If platform dependant functions are not linked with your file 
 > the *unresolved external* error will be thrown for each undefined 
 > function.

## Platform dependant functions

# What is implemented?

