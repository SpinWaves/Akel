// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 06/01/2023

#ifndef __AK_VERTEX__
#define __AK_VERTEX__

#include <Akpch.h>
#include <Maths/maths.h>

namespace Ak
{
    struct Vertex
    {
        Maths::Vec3<float> pos;
        Maths::Vec4<float> color;
        //Vec3<float> normals;
        //Vec2<float> texture_coords;
        
        static VkVertexInputBindingDescription getBindingDescription();
        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
    };
}

#endif // __AK_VERTEX__
