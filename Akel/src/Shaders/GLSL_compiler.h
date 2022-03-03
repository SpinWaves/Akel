// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/03/2022
// Updated : 03/03/2022

#ifndef __AK_SHADERS_BUILD__
#define __AK_SHADERS_BUILD__

#include <Akpch.h>

namespace Ak
{
    enum class GLSL { vertex, fragment, geometry };

    class GLSL_Compiler
    {
        public:
            GLSL_Compiler() = delete;
            
            static std::string checkShader(GLSL kind, const std::string& filename);
            static std::string compileToSPIRVasm(GLSL kind, const std::string& filename, bool optimize = false);
            static std::vector<uint32_t> compileToSPIRV(GLSL kind, const std::string& filename, bool optimize = false);

            ~GLSL_Compiler() = delete;

        private:
            static std::string readFile(const std::string& filename); 
            inline static shaderc::Compiler _compiler;
            inline static shaderc::CompileOptions _options;
    };
}

#endif // __AK_SHADERS_BUILD__
