// This file is a part of Akel
// CREATED : 18/08/2021
// UPDATED : 18/08/2021

#include <Maths/maths.h>

namespace Ak::Maths
{
    float easeInSine(float x)
    {
        return 1 - cos((x * M_PI) / 2);
    }

    float easeOutSine(float x)
    {
        return sin((x * M_PI) / 2);
    }

    float easeInOutSine(float x)
    {
        return -(cos(M_PI * x) - 1) / 2;
    }

    float easeInQuad(float x)
    {
        return x * x;
    }

    float easeOutQuad(float x)
    {
        return 1 - (1 - x) * (1 - x);
    }

    float easeInOutQuad(float x)
    {
        return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
    }

    float easeInCubic(float x)
    {
        return x * x * x;
    }

    float easeOutCubic(float x)
    {
        return 1 - pow(1 - x, 3);
    }

    float easeInOutCubic(float x)
    {
        return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
    }

    float easeInQuart(float x)
    {
        return x * x * x * x;
    }

    float easeOutQuart(float x)
    {
        return 1 - pow(1 - x, 4);
    }

    float easeInOutQuart(float x)
    {
        return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
    }

    float easeInQuint(float x)
    {
        return x * x * x * x * x;
    }

    float easeOutQuint(float x)
    {
        return 1 - pow(1 - x, 5);
    }

    float easeInOutQuint(float x)
    {
        return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
    }

    float easeInExpo(float x)
    {
        return x == 0 ? 0 : pow(2, 10 * x - 10);
    }

    float easeOutExpo(float x)
    {
        return x == 1 ? 1 : 1 - pow(2, -10 * x);
    }

    float easeInOutExpo(float x)
    {
        if(x == 0)
            return 0;
        if(x == 1)
            return 1;
        if(x < 0.5)
            return pow(2, 20 * x - 10) / 2;
        return (2 - pow(2, -20 * x + 10)) / 2;
    }
}
