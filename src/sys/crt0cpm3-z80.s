        ;; crt0cpm3-z80.s
        ;;
        ;; crt0 for CP/M 3 on Z80 / SDCC __sdcccall(1).
        ;;
        ;; Initializes data and the standard library, then calls main().
        ;; Passes argc in HL and argv in DE, and exits through BDOS.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 10.03.2026   tstih
        ;;
        .module crt0cpm

        .globl  _main
        .globl  __heap
        .globl  __argv
        .globl  __argc
        .globl  _exit
        .globl  __stdlib_init

        .area   _CODE
        ;; set up stack
        ld      sp,#stack

        ;; SDCC init global variables
        ;; no need to copy data seg. in this scenario
        call    gsinit

        ;; pass argc and argv in registers (__sdcccall(1)):
        ;;   HL = argc, DE = argv
        ld      hl, (__argc)
        ld      de, #__argv

        ;; call main
        call    _main

        ;; ------------
        ;; void _exit()
        ;; ------------
        ;; exits the current CP/M 3 process through BDOS
        ;; NOTES:
        ;;  expects the main return code in DE under SDCC(1)
        ;;  first sets BDOS process return code, then terminates to CCP
        ;; inputs: de=process return code
        ;; outputs: does not return
        ;; affects: af, bc
_exit::
        ld      c,#108
        call    5

        ;; BDOS exit: return control to CP/M.
        ld      c,#0
        jp      5

        ;; Ordering of segments for the linker (after header)
        .area   _CODE
        .area   _GSINIT
        .area   _GSFINAL
        .area   _INITIALIZER
        .area   _INITFINAL
        .area   _INITIALIZED
        .area   _HOME

        .area   _DATA
        .area   _BSEG
        .area   _BSS
        .area   _STACK
        .area   _HEAP


        ;; -------------------
        ;; void gsinit(void)
        ;; -------------------
        ;; initializes zeroed and statically initialized data
        ;; NOTES:
        ;;  clears the DATA segment, copies INITIALIZER to INITIALIZED,
        ;;  and calls the standard library initializer before main
        ;; inputs: none
        ;; outputs: initialized runtime data segments
        ;; affects: af, bc, de, hl
        .area   _GSINIT
gsinit::
        ;; zero out data.
        ld      bc, #l__DATA
        ld      a, b
        or      a, c
        jr      z, copy_data
        ld      hl, #s__DATA
        ld      (hl), #0x00
        dec     bc
        ld      a, b
        or      a, c
        jr      z, copy_data
        ld      e, l
        ld      d, h
        inc     de
        ldir
copy_data:
        ;; copy static initializations.
        ld      bc, #l__INITIALIZER
        ld      a, b
        or      a, c
        jr      z, gsinit_done
        ld      de, #s__INITIALIZED
        ld      hl, #s__INITIALIZER
        ldir
gsinit_done:
        ;; call standard library initializer
        call    __stdlib_init

        .area   _GSFINAL
        ret


        .area   _DATA
__argc::
        .dw 1                           ;; default argc is 1 (filename)
__argv::
        .ds 16                          ;; space for up to 8 argv pointers


        .area   _STACK
        .ds     1024
stack:


        .area   _HEAP
__heap::                                ;; start of heap
