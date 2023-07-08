/*
 * lst_insert.c
 *
 * Insert into linked list (at beginning).
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.06.2012   tstih
 *
 */
#include <util/list.h>

list_header_t *_list_insert(list_header_t** first, list_header_t *el) {
        el->next=*first;
        *first=el;
	return el;
}