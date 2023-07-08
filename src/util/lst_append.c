#include <util/list.h>

list_header_t *_list_append(list_header_t** first, list_header_t *el) {

	list_header_t *current;

	el->next=NULL;		/* it's always the last element */

	if (*first==NULL)	/* empty list? */
        	*first=el;
	else {
		current=*first;
		while (current->next) current=current->next;
		current->next=el;
	}
	return el;
}