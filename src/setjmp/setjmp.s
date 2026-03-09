        ;; setjmp.s
        ;;
        ;; setjmp for Z80 / SDCC __sdcccall(1).
        ;;
        ;; Saves:
        ;;   env[0] = IX
        ;;   env[1] = caller return PC
        ;;   env[2] = caller SP after returning from setjmp
        ;;
        ;; On the initial return, returns 0 in DE.

        .module setjmp

        .globl _setjmp

        .area _CODE

_setjmp::
        ld      d, h                    ; DE = env
        ld      e, l

        pop     bc                      ; caller PC, SP = post-return SP
        ld      hl, #0
        add     hl, sp                  ; HL = caller SP after return
        push    bc                      ; restore caller PC for normal ret
        ex      de, hl                  ; HL = env, DE = saved SP

        push    ix
        pop     bc
        ld      (hl), c                 ; save IX
        inc     hl
        ld      (hl), b
        inc     hl

        pop     bc
        ld      (hl), c                 ; save caller PC
        inc     hl
        ld      (hl), b
        inc     hl
        push    bc

        ld      (hl), e                 ; save caller SP
        inc     hl
        ld      (hl), d

        ld      de, #0                  ; setjmp() returns 0 initially
        ret
