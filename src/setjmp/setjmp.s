        ;; setjmp.s
        ;;
        ;; setjmp for Z80 / SDCC __sdcccall(1).
        ;;
        ;; Saves IX, the caller return PC, and the post-return SP in jmp_buf.
        ;; Returns 0 in DE on the initial return from setjmp().
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 09.03.2026   tstih
        ;;
        .module setjmp

        .globl _setjmp

        .area _CODE

        ;; ----------------------------
        ;; int setjmp(jmp_buf env)
        ;; ----------------------------
        ;; saves the current execution context in jmp_buf
        ;; NOTES:
        ;;  stores IX, the caller return PC, and the post-return SP
        ;;  so longjmp can later restore the same state
        ;; inputs: hl=env
        ;; outputs: de=0 on the initial return
        ;; affects: af, bc, de, hl
_setjmp::
        ld      d, h                    ;; DE = env
        ld      e, l

        pop     bc                      ;; caller PC, SP = post-return SP
        ld      hl, #0
        add     hl, sp                  ;; HL = caller SP after return
        push    bc                      ;; restore caller PC for normal ret
        ex      de, hl                  ;; HL = env, DE = saved SP

        push    ix
        pop     bc
        ld      (hl), c                 ;; save IX
        inc     hl
        ld      (hl), b
        inc     hl

        pop     bc
        ld      (hl), c                 ;; save caller PC
        inc     hl
        ld      (hl), b
        inc     hl
        push    bc

        ld      (hl), e                 ;; save caller SP
        inc     hl
        ld      (hl), d

        ld      de, #0                  ;; setjmp() returns 0 initially
        ret
