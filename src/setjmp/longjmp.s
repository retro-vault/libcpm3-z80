        ;; longjmp.s
        ;;
        ;; longjmp for Z80 / SDCC __sdcccall(1).
        ;;
        ;; Restores IX and SP from jmp_buf, then jumps to the saved PC.
        ;; Returns val in DE, except 0 becomes 1 per the C standard.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 09.03.2026   tstih
        ;;
        .module longjmp

        .globl _longjmp

        .area _CODE

        ;; -----------------------------------
        ;; void longjmp(jmp_buf env, int val)
        ;; -----------------------------------
        ;; restores the saved execution context and resumes at setjmp
        ;; NOTES:
        ;;  restores IX and SP from jmp_buf, reloads the saved PC,
        ;;  and jumps to it instead of returning normally
        ;;  converts val 0 to 1 to satisfy the C standard
        ;; inputs: hl=env, de=val
        ;; outputs: does not return here; resumed setjmp sees de=val or 1
        ;; affects: af, bc, de, hl, ix, sp
_longjmp::
        ld      a, d
        or      e
        jr      nz, 1$
        ld      de, #1
1$:
        push    de                      ;; preserve return value

        ld      e, (hl)                 ;; restore IX
        inc     hl
        ld      d, (hl)
        inc     hl
        push    de
        pop     ix

        ld      c, (hl)                 ;; saved PC
        inc     hl
        ld      b, (hl)
        inc     hl

        ld      e, (hl)                 ;; saved SP
        inc     hl
        ld      d, (hl)
        ex      de, hl                  ;; HL = saved SP

        pop     de                      ;; DE = longjmp return value
        ld      sp, hl
        ld      h, b
        ld      l, c
        jp      (hl)
