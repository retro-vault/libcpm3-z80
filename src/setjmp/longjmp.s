        ;; longjmp.s
        ;;
        ;; longjmp for Z80 / SDCC __sdcccall(1).
        ;;
        ;; Restores IX and SP from jmp_buf, then jumps to the saved PC.
        ;; Returns val in DE, except 0 becomes 1 per the C standard.

        .module longjmp

        .globl _longjmp

        .area _CODE

_longjmp::
        ld      a, d
        or      e
        jr      nz, longjmp_value_ok
        ld      de, #1
longjmp_value_ok:
        push    de                      ; preserve return value

        ld      e, (hl)                 ; restore IX
        inc     hl
        ld      d, (hl)
        inc     hl
        push    de
        pop     ix

        ld      c, (hl)                 ; saved PC
        inc     hl
        ld      b, (hl)
        inc     hl

        ld      e, (hl)                 ; saved SP
        inc     hl
        ld      d, (hl)
        ex      de, hl                  ; HL = saved SP

        pop     de                      ; DE = longjmp return value
        ld      sp, hl
        ld      h, b
        ld      l, c
        jp      (hl)
