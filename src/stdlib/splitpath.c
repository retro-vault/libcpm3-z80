#include <stdlib/_stdlib.h>

int splitpath(
    const char *path,
    char *drive,
    int *user,
    char *fname,
    char *ext)
{
    /* set all defaults */
    *drive = 'A' + bdos(DRV_GET, 0); /* current drive */
    *user = bdos(F_USERNUM, 0xff);   /* current user */
    strcpy(fname, "        ");       /* 8 spaces */
    strcpy(ext, "   ");              /* 3 ext */

    /* is filename empty? */
    if (strlen(path) == 0)
        return -1;

    /* does it start with a digit?*/
    unsigned char i = 0;
    char c = toupper(path[i]) & 0x7f; /* 7 bit ascii */
    if (c >= 'A' && c <= 'P' && path[i + 1] == ':')
    { /* drive */
        *drive = c;
        i += 2;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    /* c contains first leter of filename, i is index */
    unsigned char len = 0;
    /* forbidden chars in cp/m 2 */
    while (c && len < MAX_FNAME && !ispunct(c))
    {
        fname[len] = c;
        len++;
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }
    fname[len] = 0;

    /* if the end then file has no extension*/
    if (c == 0)
        return 0;

    /* must be dot! */
    if (c != '.')
        return -1;
    else
    {
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    /* get the extension */
    len = 0;
    while (c && len < MAX_EXT && !ispunct(c))
    {
        ext[len] = c;
        len++;
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }
    ext[len] = 0;

    /* if the end then we have drive, file and extension */
    if (c == 0)
        return 0;

    /* if not, then check for user area */
    if (c != '[')
        return -1;
    else
    {
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    /* optional G */
    if (c == 'G')
    {
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    /* prepare user */
    len = 0;
    char u[3];
    /* must be digit */
    if (!isdigit(c))
        return -1;
    else
    {
        u[len] = c;
        len++;
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    /* can be the second digit */
    if (isdigit(c))
    {
        u[len] = c;
        len++;
        i++;
        c = toupper(path[i]) & 0x7f; /* next char */
    }

    u[len] = 0;
    *user = atoi(u);
    /* user area must be in range */
    if (*user < 0 || *user > 15)
        return -1;

    /* must conclude with ] */
    if (c != ']')
        return -1;

    /* and that's it. ignore the rest! */
    return 0;
}