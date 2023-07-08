float modf(float x, float *y)
{
    *y = (long)x;
    return (x - *y);
}