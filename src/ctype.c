/*
 * ctype.h
 *
 * Standard C character functions.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 02.05.2021   tstih
 *
 */
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isalpha(int c)
{
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isspace(int c)
{
   return c == ' ' || c == '\t'; // || whatever other char you consider space
}

bool ispunct(int c)
{
   static const char *punct = ".;!?...";
   return strchr(punct, c) == NULL ? FALSE : TRUE; // you can make this shorter
}

int tolower(int c)
{
   if ( !isalpha(c) ) return c;
   return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}