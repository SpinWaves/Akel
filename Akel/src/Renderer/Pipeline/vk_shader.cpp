// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 01/05/2022

#include "vk_graphic_pipeline.h"

#include <Utils/fStrings.h>
#include <Modules/GLSL/GLSL_compiler.h>

namespace Ak
{
	Shader load_spirv_shader_from_file(const fString& path, Shader::type t)
	{

	}

	Shader load_spirv_shader_from_file(const fString& path)
	{
		fString fileExt = 
		for(int i = 0; i < fileExt.size(); i++)
			fileExt[i] = std::tolower(fileExt[i]);

		Shader::type type;

		if(fileExt == ".comp")		type = Shader::type::compute
		else if(fileExt == ".vert") type = Shader::type::vertex;
		else if(fileExt == ".tesc") type = Shader::type::tesselation_control;
		else if(fileExt == ".tese") type = Shader::type::tesselation_evaluation;
		else if(fileExt == ".geom") type = Shader::type::geometry;
		else if(fileExt == ".frag") type = Shader::type::fragment;
		else Core::log::report(FATAL_ERROR, "Vulkan : unable to deduce the type of a shader from its extension (unrecognised GLSL extension : %s)", fileExt.c_str());
	}

	Shader::Shader(const std::vector<uint32_t> byte_code, Shader::type t) : _byte_code(std::move(byte_code)), _type(t) {}

	void Shader::generate()
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = _byte_code.size();
		createInfo.pCode = _byte_code.data();

		if(vkCreateShaderModule(Render_Core::get().getDevice().get(), &createInfo, nullptr, &_shader) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create shader module");
	}
}
