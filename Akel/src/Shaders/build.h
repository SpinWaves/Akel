// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/09/2021
// Updated : 03/03/2022

#ifndef __AK_SHADERS_BUILD_BASICS_2D__
#define __AK_SHADERS_BUILD_BASICS_2D__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    std::string compileShaderSPIRVassembly(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false);
    std::vector<uint32_t> compileShaderSPIRV(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false);

    void buildBasics2D();
}

#endif // __AK_SHADERS_BUILD_BASICS_2D__
