        ;; bdos.s
        ;; 
        ;; cp/m bdos and extended bdos calls
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
		;; 26.04.2021   tstih
        .module bdos

        .globl _bdos
        .globl _bdosret

        .equ    BDOS, 5

        .area   _CODE

        ;; -----------------------------------------
        ;; uint8_t bdos(uint8_t fn, uint16_t param);
        ;; -----------------------------------------
        ;; calls cp/m bdos
        ;; affect:  af, bc, de, hl
_bdos::
        push    ix                      ; store ix
		call    rawbdos                 ; raw bdos fn call
		pop     ix                      ; restore ix
        ld      l,a                     ; return a
		ret


        ;; ---------------------------------------------------------------
        ;; bdos_ret_t *bdosret(uint8_t fn, uint16_t param, bdos_ret_t *p);
        ;; ---------------------------------------------------------------
        ;; calls cp/m bdos and store result to variables
        ;; output: a, b, hl populated with ret. values
        ;; affect:  af, bc, de, hl
_bdosret::
        ;; classic bdos call!
        push    ix
        call    rawbdos
		;; store ret value to de.
		ex      de, hl      
        ;; get bdos_ret_t *p to hl
		ld      l,3(ix)
		ld      h,4(ix) 
        push    hl                      ; store pointer as return value
        ld      (hl),a                  ; store a
        inc     hl
        ld      (hl),b                  ; store b
        inc     hl
        ld      (hl),e                  ; and hl
        inc     hl
        ld      (hl),d
        ;; restore return value
        pop     hl
        ;; clean stack and exit
		pop     ix                      ; restore ix
		ret


        ;; raw bdos call
        ;; input:	bdos_call_t struct pointer on stack
        ;; output:  ix=stack, (a,b,de)=potential result
        ;; affect:  af, bc, de, hl, ix
rawbdos:
        ld      ix,#6
		add     ix,sp                   ; ix=sp
		ld      c,(ix)                  ; bdos function into c.
		ld      e,1(ix)                 ; load bdos parameter into de
		ld      d,2(ix)
		call    BDOS                    ; make BDOS call!
        ret