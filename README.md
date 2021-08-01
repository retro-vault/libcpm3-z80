# libcpm3-z80

**libcpm3-z80** is a **portable**, **readable**, and **minimal** [ISO/IEC 9899:TC2](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) *Standard C Library* for Digital Research's CP/M 3.

Implementing a standard library shouldn't be a daunting task. Unless the library immoderately aspires to target all architectures and all compilers by using sophisticated preprocessor directives and tricks, 
only known to god and a few earthlings.

**libcpm3-z80** is an attempt to provide a library, written in purest C, with a clear separation of platform independent and platform dependent code. To port it to your architecture you need to provide a handful of well documented platform specific functions that the standard requires and are not available in CP/M's BDOS.

