#include <math/_math.h>

float log(float x)
{
    float Rz;
    float f, z, w, znum, zden, xn;
    int n;

    if (x <= 0.0f)
    {
        errno = EDOM;
        return 0.0f;
    }
    f = frexp(x, &n);
    znum = f - 0.5;
    if (f > CL0)
    {
        znum -= 0.5;
        zden = (f * 0.5) + 0.5;
    }
    else
    {
        n--;
        zden = znum * 0.5 + 0.5;
    }
    z = znum / zden;
    w = z * z;

    Rz = z + z * (w * A(w) / B(w));
    xn = n;
    return ((xn * CL2 + Rz) + xn * CL1);
}