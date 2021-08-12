// This file is a part of Akel
// CREATED : 04/04/2021
// UPDATED : 12/08/2021

#include <Maths/maths.h>

namespace Ak::Maths
{
    int randint(int a, int b)
    {
        return rand() % (b - a) + a;
    }

    bool rand_probability(double proba)
    {
        if(proba < 1)
            return ((double)rand() / (double)RAND_MAX < proba);
        else if(proba >= 1)
            return true;
        return false;
    }

    float rsqrt(float number)
    {
        long i = 0;
        float x2 = 0.0f;
        float y = 0;
        const float threehalfs = 1.5f;   // Quake III algorithm

        x2 = number * 0.5f;
        y = number;
        i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y));

        return y;
    }
}
