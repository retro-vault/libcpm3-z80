#include <math/_math.h>

float fabs(float x)
{
    union _float_long fl;

    fl.f = x;
    fl.l &= 0x7fffffff;
    return fl.f;
}