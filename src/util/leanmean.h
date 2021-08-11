/*
 * leanmean.h
 *
 * Defines LEAN_AND_MEAN flag.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 11.08.2021   tstih
 *
 */
#ifndef __LEANMEAN_H__
#define __LEANMEAN_H__

/* Check for LEAN_AND_MEAN */
#define _EXPAND(VAL)    VAL ## 1
#define EXPAND(VAL)     _EXPAND(VAL)
#if !defined(SLIM) || (EXPAND(SLIM) == 1) 
#undef LEAN_AND_MEAN
#else
#define LEAN_AND_MEAN
#endif

#endif