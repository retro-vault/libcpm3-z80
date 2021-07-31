# μlibc

**Portable**, **readable**, and **minimal** *Standard C Library* for simple machines.

# Why μlibc?

Implementing a standard library on a custom hardware shouldn't be a daunting
task. Unless the library immoderately aspires to target all architectures and
all compilers by using sophisticated preprocessor directives and tricks, 
only known to god and a few earthlings.

Not μlibc! This library is written in purest ANSI C, with clear separation of
platform dependent and platform independent code.

## How does it work?

You type `./configure` and we ask you a bunch of questions about your 
target system. Then we build a clean **source code** of μlibc for you, 
and ask you to provide a few platform specific functions. 

Once you write those, you are good to go.

We try to follow [ISO/IEC 9899:TC2](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf).