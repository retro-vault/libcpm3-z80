#include <stdbool.h>
#include <string.h>

bool ispunct(int c)
{
    /* ...also CP/M 2 forbidden characters in files */
    static const char *punct = "<>.,;:=?*[]%|()/\\";
    return strchr(punct, c) == NULL ? FALSE : TRUE; // you can make this shorter
}