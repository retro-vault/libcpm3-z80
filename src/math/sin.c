#include <math/_math.h>

float sin(float x)
{
    if (x == 0.0f)
        return 0.0f;
    return _sincosf(x, 0);
}