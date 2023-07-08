int toupper(int c)
{
    if (('a' <= c) && (c <= 'z'))
        return 'A' + (c - 'a');
    else
        return c;
}