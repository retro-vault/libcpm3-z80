        ;; bdos.s
        ;;
        ;; bdos and bdosret for Z80 / SDCC __sdcccall(1).
        ;;
        ;; Calls CP/M BDOS function 5 using SDCC(1) register arguments.
        ;; bdos returns A; bdosret stores A/B/HL into a result struct.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 10.03.2026   tstih
        ;;
        .module bdos

        .globl _bdos
        .globl _bdosret

        .equ    BDOS, 5

        .area   _CODE

        ;; -----------------------------------
        ;; uint8_t bdos(uint8_t fn, uint16_t param)
        ;; -----------------------------------
        ;; calls CP/M BDOS function 5 and returns register A
        ;; NOTES:
        ;;  uses SDCC(1) argument passing
        ;;  preserves IX and IY across the BIOS entry
        ;; inputs: a=fn, de=param
        ;; outputs: a=BDOS return byte
        ;; affects: af, bc, de, hl
_bdos::
        push    ix
        push    iy
        ld      c, a                    ;; C = fn (from A)
        call    BDOS                    ;; DE = param (already in DE)
        pop     iy
        pop     ix
        ret


        ;; ----------------------------------------------------------
        ;; bdos_ret_t *bdosret(uint8_t fn, uint16_t param, bdos_ret_t *p)
        ;; ----------------------------------------------------------
        ;; calls CP/M BDOS function 5 and stores A, B, and HL in *p
        ;; NOTES:
        ;;  uses SDCC(1) argument passing with p on the stack
        ;;  performs callee cleanup for the stack-passed pointer
        ;;  preserves IX and IY across the BIOS entry
        ;; inputs: a=fn, de=param, stack=p
        ;; outputs: de=p, *p={ reta=A, retb=B, rethl=HL }
        ;; affects: af, bc, de, hl
_bdosret::
        push    ix
        ld      ix, #4
        add     ix, sp                  ;; ix = &p (sp+4 after push ix)
        ld      l, (ix)                 ;; read p into HL
        ld      h, 1(ix)
        push    hl                      ;; save p
        push    iy
        ld      c, a                    ;; C = fn (from A)
        call    BDOS                    ;; A=result_A, B=result_B, HL=result_HL
        pop     iy
        ex      de, hl                  ;; DE = BDOS result HL
        pop     hl                      ;; HL = p
        push    hl                      ;; save p for return value
        ld      (hl), a                 ;; store result A
        inc     hl
        ld      (hl), b                 ;; store result B
        inc     hl
        ld      (hl), e                 ;; store result HL low
        inc     hl
        ld      (hl), d                 ;; store result HL high
        pop     de                      ;; DE = p (return value for sdcccall(1))
        pop     ix                      ;; restore ix
        pop     bc                      ;; BC = return address
        pop     hl                      ;; discard stack-passed p
        push    bc                      ;; restore return address for RET
        ret
