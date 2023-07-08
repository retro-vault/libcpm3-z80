#include <util/list.h>

list_header_t* _list_find(
        list_header_t *first,
        list_header_t **prev,
        uint8_t ((*match)(list_header_t *p, uint16_t arg)),
        uint16_t the_arg)
        {
        /* assume no previous */
        *prev=NULL;
	while (first && !match(first,the_arg)) {
	        *prev=first;
	        first=first->next;
	}
        /* result is in first */
        return first; 
}