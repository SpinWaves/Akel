// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/03/2022
// Updated : 30/04/2022

#include <Core/core.h>
#include <Modules/GLSL/GLSL_compiler.h>

namespace Ak
{
    std::string GLSL_Compiler::readFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if(!file.is_open())
            Core::log::report(FATAL_ERROR, "GLSL Compiler : failed to open shader file");

        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    std::string GLSL_Compiler::checkShader(GLSL kind, const std::string& filename)
    {
        shaderc_shader_kind __kind;
        switch(kind)
        {
            case GLSL::vertex : __kind = shaderc_vertex_shader; break;
            case GLSL::fragment : __kind = shaderc_fragment_shader; break;
            case GLSL::geometry : __kind = shaderc_geometry_shader; break;

            default : Core::log::report(ERROR, "GLSL Compiler : unknown shader type"); return "";
        }
        
        shaderc::PreprocessedSourceCompilationResult result = _compiler.PreprocessGlsl(readFile(filename), __kind, filename.c_str(), _options);

        if(result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            Core::log::report(ERROR, std::move(std::string("GLSL Compiler : ") + result.GetErrorMessage()));
            return "";
        }

        return {result.cbegin(), result.cend()};
    }

    std::string GLSL_Compiler::compileToSPIRVasm(GLSL kind, const std::string& filename, bool optimize)
    {
        shaderc_shader_kind __kind;
        switch(kind)
        {
            case GLSL::vertex : __kind = shaderc_vertex_shader; break;
            case GLSL::fragment : __kind = shaderc_fragment_shader; break;
            case GLSL::geometry : __kind = shaderc_geometry_shader; break;

            default : Core::log::report(ERROR, "GLSL Compiler : unknown shader type"); return "";
        }
        shaderc::Compiler _compiler;
        shaderc::CompileOptions _options;

        if(optimize)
            _options.SetOptimizationLevel(shaderc_optimization_level_size);

        shaderc::AssemblyCompilationResult result = _compiler.CompileGlslToSpvAssembly(readFile(filename), __kind, filename.c_str(), _options);

        if(result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            Core::log::report(ERROR, std::move(std::string("GLSL Compiler : ") + result.GetErrorMessage()));
            return "";
        }

        return {result.cbegin(), result.cend()};
    }

    std::vector<uint32_t> GLSL_Compiler::compileToSPIRV(GLSL kind, const std::string& filename, bool optimize)
    {
        shaderc_shader_kind __kind;
        switch(kind)
        {
            case GLSL::vertex : __kind = shaderc_vertex_shader; break;
            case GLSL::fragment : __kind = shaderc_fragment_shader; break;
            case GLSL::geometry : __kind = shaderc_geometry_shader; break;

            default : Core::log::report(ERROR, "GLSL Compiler : unknown shader type"); return sstd::vector<uint32_t>();
        }
        shaderc::Compiler _compiler;
        shaderc::CompileOptions _options;

        if(optimize)
            _options.SetOptimizationLevel(shaderc_optimization_level_size);

        shaderc::SpvCompilationResult module = _compiler.CompileGlslToSpv(readFile(filename), __kind, filename.c_str(), _options);

        if(module.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            Core::log::report(ERROR, std::move(std::string("GLSL Compiler : ") + module.GetErrorMessage()));
            return std::vector<uint32_t>();
        }

        return {module.cbegin(), module.cend()};
    }
}
