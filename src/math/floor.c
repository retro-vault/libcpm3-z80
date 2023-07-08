float floor(float x)
{
    long r;
    r = x;
    if (r <= 0)
        return (r + ((r > x) ? -1 : 0));
    else
        return r;
}