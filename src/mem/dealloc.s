        ;; dealloc.s
        ;;
        ;; Deallocate a memory block on the heap.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 18.02.2026   tstih
        .module dealloc

        .globl  __dealloc
        .globl  _merge_with_next

        .equ    ALLOCATED, 0x01
        .equ    BLK_SIZE, 5

        .area   _CODE

        ;; --------------------------------------------------------
        ;; void _dealloc(uint16_t heap, void *p)
        ;; --------------------------------------------------------
        ;; input:
        ;;   4(ix): heap low
        ;;   5(ix): heap high
        ;;   6(ix): p low
        ;;   7(ix): p high
__dealloc::
        push    ix
        ld      ix,#0
        add     ix,sp

        ;; free(NULL) is no-op
        ld      l,6(ix)
        ld      h,7(ix)
        ld      a,h
        or      l
        jr      z,dealloc_ret

        ;; target block = p - BLK_SIZE -> bc
        ld      de,#BLK_SIZE
        or      a
        sbc     hl,de
        ld      c,l
        ld      b,h

        ;; prev = 0 (de), cur = heap (hl)
        ld      de,#0
        ld      l,4(ix)
        ld      h,5(ix)

dealloc_find:
        ld      a,h
        or      l
        jr      z,dealloc_ret                  ; block not found

        ld      a,h
        cp      b
        jr      nz,dealloc_step
        ld      a,l
        cp      c
        jr      z,dealloc_found

dealloc_step:
        ld      d,h
        ld      e,l                            ; prev = cur
        ld      c,(hl)
        inc     hl
        ld      h,(hl)
        ld      l,c                            ; cur = cur->next
        jr      dealloc_find

dealloc_found:
        ;; cur->stat = NEW
        push    hl
        inc     hl
        inc     hl
        ld      (hl),#0
        pop     hl

        ;; if (prev && !(prev->stat & ALLOCATED)) merge(prev), cur=prev
        ld      a,d
        or      e
        jr      z,dealloc_next

        push    hl                             ; preserve cur
        ld      h,d
        ld      l,e
        inc     hl
        inc     hl
        ld      a,(hl)
        pop     hl
        and     #ALLOCATED
        jr      nz,dealloc_next

        push    hl                             ; preserve cur
        ld      h,d
        ld      l,e
        push    hl
        call    _merge_with_next
        pop     bc
        pop     hl
        ld      h,d
        ld      l,e                            ; cur = prev

dealloc_next:
        ;; if (cur->next && !(next->stat & ALLOCATED)) merge(cur)
        ld      c,(hl)
        inc     hl
        ld      b,(hl)
        dec     hl
        ld      a,b
        or      c
        jr      z,dealloc_ret

        push    hl                             ; preserve cur
        ld      h,b
        ld      l,c
        inc     hl
        inc     hl
        ld      a,(hl)
        pop     hl
        and     #ALLOCATED
        jr      nz,dealloc_ret

        push    hl
        call    _merge_with_next
        pop     bc

dealloc_ret:
        pop     ix
        ret
