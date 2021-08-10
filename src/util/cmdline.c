/*
 * cmdline.c
 *
 * Initializing CP/M command line arguments.
 * 
 * NOTES:
 *  Based on https://github.com/dmo9000/cpmlibc
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 04.08.2012   tstih
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Max. number of arguments */
#define MAX_ARGS    8
/* Arg. buffer */
#define TBUFF       0x80

/* argc from crt0cpm-z80.s */
extern void *_argc;
/* argv from crt0cpm-z80.s */
extern void *_argv;

void _init_cmdline() {
        /* standard CP/M command buffer */
    char *argptr = (char *) TBUFF; 
    unsigned char abytes;
    int i = 0;
    bool within_arg = false;
    int acount = 1;
    uint16_t *pcount=(uint16_t *)&_argc;

    /* first argv is filename, populated by crt0.s */
    uint16_t *argv_ptr = (uint16_t*)&_argv;
    memset((void *)argv_ptr, 0, 0x10);
    argv_ptr[0]=(uint16_t)NULL;
    argv_ptr++;    
    abytes=argptr[0];
    for (i = 1; i < (abytes+2 ); i++) {
        switch(argptr[i]) {
        case '\0':
            if (within_arg) 
                acount++;
            within_arg = false;
            if (acount >= MAX_ARGS) {
                goto args_done;
            }
            break;
        case ' ':
            argptr[i] = '\0';
            if (within_arg)
                acount++;
            if (acount >= MAX_ARGS) {
                goto args_done;
            }
            within_arg = false;
            break;
        default:
            if (!within_arg) {
                argv_ptr[0] = 0x80+i; 
                argv_ptr[1] = 0x00;  
                argv_ptr++;
                within_arg = true;
            } 
            break;
        }
    }
args_done:
    *pcount = acount;
}