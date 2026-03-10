/*
 * _list_remove_first.c
 *
 * Remove and return the first node from an internal linked list.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_list.h"

_list_header_t *_list_remove_first(_list_header_t **first) {
	_list_header_t *result;	
	if (*first==NULL) return NULL; /* empty list */
	result=*first;
	*first = (_list_header_t*) ((*first)->next);
	return result;
}
