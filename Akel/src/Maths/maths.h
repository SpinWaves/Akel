// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 23/03/2022

#ifndef __AK_MATH__
#define __AK_MATH__

#include <Maths/vec2.h>
#include <Maths/vec3.h>
#include <Maths/vec4.h>

#include <Maths/easings.h>

#include <Akpch.h>

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

namespace Ak::Maths
{
    int randint(int a, int b);
    bool rand_probability(double proba);
    float rsqrt(float number);

    // Better implementation of abs functions
    inline int abs(int a) noexcept
    {
        int mask = (a >> (sizeof(int) * CHAR_BIT - 1));
        return (a + mask) ^ mask;
    }

    inline float abs(float a) noexcept
    {
        long i = *(long*)&a; // tricky convertion
        i &= ~(1u << 31); // set sign to 0 makes it positive
        return *(float*)&i; // another tricky convertion
    }
}

#endif // __AK_MATH__
