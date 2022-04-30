// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 30/04/2022

#include "vk_graphic_pipeline.h"

#include <Utils/fStrings.h>
#include <Modules/GLSL/GLSL_compiler.h>

namespace Ak
{
	Shader::Shader(const std::filesystem::path path, Shader::lang l, Shader::type t) : _file(std::move(path)), _type(t), _lang(l) {}
	Shader::Shader(const std::filesystem::path path, Shader::lang l) : _file(std::move(path)), _lang(l)
	{
		if(l != Shader::lang::glsl)
			Core::log::report(FATAL_ERROR, "Vulkan : unable to deduce the type of a shader from its extension (works only for GLSL shaders)");

		auto fileExt = _file.extension().string();
		for(int i = 0; i < fileExt.size(); i++)
			fileExt[i] = std::tolower(fileExt[i]);

		if(fileExt == ".comp") { _type = Shader::type::compute; return; }
		if(fileExt == ".vert") { _type = Shader::type::vertex; return; }
		if(fileExt == ".tesc") { _type = Shader::type::tesselation_control; return; }
		if(fileExt == ".tese") { _type = Shader::type::tesselation_evaluation; return; }
		if(fileExt == ".geom") { _type = Shader::type::geometry; return; }
		if(fileExt == ".frag") { _type = Shader::type::fragment; return; }

		Core::log::report(FATAL_ERROR, "Vulkan : unable to deduce the type of a shader from its extension (unrecognised GLSL extension : %s)", fileExt.c_str());
	}

	void Shader::generate()
	{
		const std::vector<uint32_t> byte_code;

		if(_lang == Shader::lang::glsl)
		{
			GLSL_Compiler comp;
			switch(_type)
			{
				case Shader::type::vertex: byte_code = comp.compileToSPIRV(GLSL::vertex, _name.c_str(), true); break;
				case Shader::type::fragment: byte_code = comp.compileToSPIRV(GLSL::fragment, _name.c_str(), true); break;
				case Shader::type::geometry: byte_code = comp.compileToSPIRV(GLSL::geometry, _name.c_str(), true); break;
				case Shader::type::tesselation_evaluation: byte_code = comp.compileToSPIRV(GLSL::tesselation_evaluation, _name.c_str(), true); break;
				case Shader::type::tesselation_control: byte_code = comp.compileToSPIRV(GLSL::tesselation_control, _name.c_str(), true); break;
				case Shader::type::compute: byte_code = comp.compileToSPIRV(GLSL::compute, _name.c_str(), true); break;
			}
		}
		
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = byte_code.size() * (_lang == Shader::lang::glsl ? 4 : 1);
		createInfo.pCode = byte_code.data();

		if(vkCreateShaderModule(Render_Core::get().getDevice().get(), &createInfo, nullptr, &_shader) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create shader module");
	}
}
