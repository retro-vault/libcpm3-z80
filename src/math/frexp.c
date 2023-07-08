#include <math/_math.h>

float frexp(float x, int *pw2)
{
    union _float_long fl;
    long int i;

    fl.f = x;
    /* Find the exponent (power of 2) */
    i = (fl.l >> 23) & 0x000000ff;
    i -= 0x7e;
    *pw2 = i;
    fl.l &= 0x807fffff; /* strip all exponent bits */
    fl.l |= 0x3f000000; /* mantissa between 0.5 and 1 */
    return (fl.f);
}