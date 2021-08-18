// This file is a part of Akel
// CREATED : 04/04/2021
// UPDATED : 18/08/2021

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
}

#endif // __AK_MATH__
