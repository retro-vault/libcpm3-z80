#include <math/_math.h>

float ldexp(float x, int pw2)
{
    union _float_long fl;
    long e;

    fl.f = x;

    e = (fl.l >> 23) & 0x000000ff;
    e += pw2;
    fl.l = ((e & 0xff) << 23) | (fl.l & 0x807fffff);

    return (fl.f);
}