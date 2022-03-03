// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/09/2021
// Updated : 03/03/2022

#include <Shaders/build.h>

namespace Ak
{
    std::string compileShaderSPIRVassembly(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false)
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;

        if(optimize)
            options.SetOptimizationLevel(shaderc_optimization_level_size);

        shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(
            source, kind, source_name.c_str(), options);

        if(result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            std::cerr << result.GetErrorMessage();
            return "";
        }

        return {result.cbegin(), result.cend()};
    }

    std::vector<uint32_t> compileShaderSPIRV(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false)
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;

        if(optimize)
            options.SetOptimizationLevel(shaderc_optimization_level_size);

        shaderc::SpvCompilationResult module =
            compiler.CompileGlslToSpv(source, kind, source_name.c_str(), options);

        if(module.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            std::cerr << module.GetErrorMessage();
            return std::move(std::vector<uint32_t>());
        }

        return {module.cbegin(), module.cend()};
    }

    void buildBasics2D()
    {
        if(!std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.frag.spv") && !std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.vert.spv"))
        {
            std::system(std::string("glslangValidator -V " + Core::getShaderPath() + "basic_2D/basic_2D.frag -o " + Core::getShaderPath() + "basic_2D/basic_2D.frag.spv").c_str());
            std::system(std::string("glslangValidator -V " + Core::getShaderPath() + "basic_2D/basic_2D.vert -o " + Core::getShaderPath() + "basic_2D/basic_2D.vert.spv").c_str());
            if(!std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.frag.spv") && !std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.vert.spv"))
                Core::log::report(FATAL_ERROR, "Shaders : basic 2D shader cannot be build");
            else
                Core::log::report(MESSAGE, "Shaders : basic 2D shader built");
        }
    }
}
