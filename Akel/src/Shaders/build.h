// This file is a part of Akel
// CREATED : 29/09/2021
// UPDATED : 29/09/2021

#ifndef __AK_SHADERS_BUILD_BASICS_2D__
#define __AK_SHADERS_BUILD_BASICS_2D__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    void buildBasics2D()
    {
        for(auto& p: std::filesystem::directory_iterator(getShaderPath() + "basic_2D"))
        {
            if(!std::filesystem::exists("basic_2D.frag.spv") && !std::filesystem::exists("basic_2D.vert.spv"))
            {
                std::system("glslangValidator -V basic_2D.frag -o basic_2D.frag.spv");
                std::system("glslangValidator -V basic_2D.vert -o basic_2D.vert.spv");
                Core::log::report(MESSAGE, "Shaders : basic 2D shader built");
            }
        }
    }
}

#endif // __AK_SHADERS_BUILD_BASICS_2D__
