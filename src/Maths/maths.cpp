// This file is a part of Akel
// CREATED : 04/04/2021
// UPDATED : 04/04/2021

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
}
