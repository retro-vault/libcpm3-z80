/*
 * _list_insert.c
 *
 * Insert a node at the head of an internal singly-linked list.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_list.h"

_list_header_t *_list_insert(_list_header_t** first, _list_header_t *el) {
        el->next=*first;
        *first=el;
	return el;
}
