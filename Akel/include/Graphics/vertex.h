// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 31/01/2023

#ifndef __AK_VERTEX__
#define __AK_VERTEX__

#include <Akpch.h>
#include <Maths/maths.h>
#include <Core/profile.h>

namespace Ak
{
    struct AK_API Vertex
    {
        Maths::Vec3<float> pos;
        Maths::Vec4<float> color;
		Maths::Vec2<float> texture_coords;
        //Maths::Vec3<float> normals;
        
        static VkVertexInputBindingDescription getBindingDescription();
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
    };
}

#endif // __AK_VERTEX__
