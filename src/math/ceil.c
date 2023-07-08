float ceil(float x)
{
    long r;
    r = x;
    if (r < 0)
        return r;
    else
        return (r + ((r < x) ? 1 : 0));
}