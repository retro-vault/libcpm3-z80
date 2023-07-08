/*
 * lst_match.c
 *
 * Match an item in linked list (compare fn)
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.06.2012   tstih
 *
 */
#include <util/list.h>

uint8_t _list_match_eq(list_header_t *p, uint16_t arg) {
        return ( ((uint16_t)p) == arg );
}