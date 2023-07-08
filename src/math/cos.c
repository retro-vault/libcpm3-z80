#include <math/_math.h>

float cos(float x)
{
    if (x == 0.0f)
        return 1.0f;
    return _sincosf(x, 1);
}