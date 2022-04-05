// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 05/04/2022

#include "vk_graphic_pipeline.h"

#include <Utils/fStrings.h>
#include <Modules/GLSL/GLSL_compiler.h>

namespace Ak
{
	Shader::Shader(const fString path, Shader::type t) : _name(std::move(path)), _type(t) {}

	void Shader::generate()
	{
		const std::vector<uint32_t> byte_code = GLSL_Compiler::compileToSPIRV(_type == Shader::type::vertex ? GLSL::vertex : GLSL::fragment, _name.c_str(), true);
		
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = byte_code.size() * 4; // times 4 because codeSize takes size in bytes, not uint32_t
		createInfo.pCode = bute_code.data();

		if(vkCreateShaderModule(Render_Core::get().getDevice()->get(), &createInfo, nullptr, &_shader) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create shader module");
	}
}
