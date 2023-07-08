int tolower(int c)
{
    if (('A' <= c) && (c <= 'Z'))
        return 'a' + (c - 'A');
    else
        return c;
}