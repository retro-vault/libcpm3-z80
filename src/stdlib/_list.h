/*
 * list.h
 *
 * Linked list header file.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.06.2012   tstih
 *
 */
#ifndef LIBCPM3_UTIL_LIST_H
#define LIBCPM3_UTIL_LIST_H

#include <stdint.h>
#include <stdlib.h>

/* each linked list must start with _list_header */
typedef struct _list_header_s {
    void *next;
} _list_header_t;

/* match functions */
extern uint8_t _list_match_eq(_list_header_t *p, uint16_t arg);

/* find element using match function */
extern _list_header_t *_list_find(
    _list_header_t *first,
    _list_header_t **prev,
    uint8_t (*match)(_list_header_t *p, uint16_t arg),
    uint16_t the_arg);

/* insert element into linked list at begining */
extern _list_header_t *_list_insert(_list_header_t** first, _list_header_t *el);

/* insert element into linked list at end */
extern _list_header_t *_list_append(_list_header_t** first, _list_header_t *el);

/* removes element from linked list */
extern _list_header_t *_list_remove(_list_header_t **first, _list_header_t *el);

/* remove first element from linked list */
extern _list_header_t *_list_remove_first(_list_header_t **first);

#endif /* LIBCPM3_UTIL_LIST_H */
