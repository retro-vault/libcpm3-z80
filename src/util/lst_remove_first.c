/*
 * lst_remove_first.c
 *
 * Remove first element from linked list.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.06.2012   tstih
 *
 */
#include <util/list.h>

list_header_t *_list_remove_first(list_header_t **first) {
	list_header_t *result;	
	if (*first==NULL) return NULL; /* empty list */
	result=*first;
	*first = (list_header_t*) ((*first)->next);
	return result;
}