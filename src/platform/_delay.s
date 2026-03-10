        ;; _delay.s
        ;;
        ;; delay helper for Z80 platform timing.
        ;;
        ;; Implements an exact 1 ms busy-wait on a 4 MHz Z80.
        ;; Used internally by _msleep().
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2026 tomaz stih
        ;;
        ;; 10.03.2026   tstih
        ;;
        .module _delay
        .globl  __delay_1ms

        .area   _CODE

        ;; ---------------------
        ;; void __delay_1ms(void)
        ;; ---------------------
        ;; delays for exactly 1 ms on a 4 MHz Z80
        ;; NOTES:
        ;;  must be entered via CALL because the timing budget includes it
        ;;  uses a fixed-count loop to reach 4000 T-states total
        ;; inputs: none
        ;; outputs: none
        ;; affects: af, b, hl
__delay_1ms::
        ld      b,#209          ;; 7 T
1$:
        dec     hl              ;; 6 T  (timing fill, HL value unused)
        djnz    1$              ;; 13/8 T
        ret                     ;; 10 T
