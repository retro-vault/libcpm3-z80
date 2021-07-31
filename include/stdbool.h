/*
 * stdbool.h
 *
 * Standard C boolean type. 
 * 
 * NOTES:
 *  This does not expand to _Bool and does not define macro
 *  __bool_true_false_are_defined as required by ISO 9899:TC2 7.16.
 *  It simply defines you a bool, and true and false constants in
 *  small case and capital case.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 19.06.2021   tstih
 *
 */
#ifndef __STDBOOL_H__
#define __STDBOOL_H__

#define bool int

#define false 0
#define FALSE 0
#define true 1
#define TRUE 1

#endif /* __STDBOOL_H__ */
