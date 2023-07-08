#include <util/list.h>

list_header_t *_list_remove_first(list_header_t **first) {
	list_header_t *result;	
	if (*first==NULL) return NULL; /* empty list */
	result=*first;
	*first = (list_header_t*) ((*first)->next);
	return result;
}