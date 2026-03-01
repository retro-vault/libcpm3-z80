        ;; alloc.s
        ;;
        ;; Allocate a memory block on the heap.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 18.02.2026   tstih
        .module alloc
        .optsdcc -mz80 sdcccall(1)

        .globl  __alloc
        .globl  _split

        .equ    ALLOCATED, 0x01
        .equ    BLK_SIZE, 5
        .equ    SPLIT_THR, 9                   ; BLK_SIZE + MIN_CHUNK_SIZE

        .area   _CODE

        ;; --------------------------------------------------------
        ;; void *_alloc(uint16_t heap, size_t size)
        ;; --------------------------------------------------------
        ;; input:
        ;;   hl = heap
        ;;   de = size
        ;; output:
        ;;   hl = ptr or 0
__alloc::
        ;; keep requested size in bc across the scan
        ld      b,d
        ld      c,e

        ;; hl is current block already

alloc_loop:
        ld      a,h
        or      l
        jr      z,alloc_fail

        ;; if (b->stat & ALLOCATED) next
        push    hl
        inc     hl
        inc     hl
        ld      a,(hl)
        pop     hl
        and     #ALLOCATED
        jr      nz,alloc_next

        ;; bc = b->size
        push    hl
        inc     hl
        inc     hl
        inc     hl
        ld      c,(hl)
        inc     hl
        ld      b,(hl)
        pop     hl

        ;; if (b->size < size) next
        ld      a,b
        cp      d
        jr      c,alloc_next
        jr      nz,alloc_found
        ld      a,c
        cp      e
        jr      c,alloc_next

alloc_found:
        ;; diff = b->size - size
        ld      a,c
        sub     e
        ld      c,a
        ld      a,b
        sbc     a,d
        ld      b,a

        ;; split if diff > SPLIT_THR
        ld      a,b
        or      a
        jr      nz,alloc_split
        ld      a,c
        cp      #10
        jr      c,alloc_no_split

alloc_split:
        push    hl                              ; preserve b
        ld      d,b
        ld      e,c                             ; de = requested size
        call    _split
        pop     hl

alloc_no_split:
        ;; b->stat = ALLOCATED
        push    hl
        inc     hl
        inc     hl
        ld      (hl),#ALLOCATED
        pop     hl

        ;; return b->data
        ld      bc,#BLK_SIZE
        add     hl,bc
        jr      alloc_ret

alloc_next:
        ;; b = b->hdr.next
        ld      c,(hl)
        inc     hl
        ld      h,(hl)
        ld      l,c
        jr      alloc_loop

alloc_fail:
        ld      hl,#0

alloc_ret:
        ret
