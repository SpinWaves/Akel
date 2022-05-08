// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 08/05/2022

#include "vk_shader.h"
#include "vk_graphic_pipeline.h"

#include <Utils/fStrings.h>

namespace Ak
{
	Shader load_spirv_from_file(fString path, Shader::type t)
	{
		std::ifstream stream(path.c_str(), std::ios::binary);

		if(!stream.is_open())
			Core::log::report(FATAL_ERROR, "Vulkan : cannot open spirv shader file");
		std::vector<uint32_t> data;

		stream.seekg(0);
		std::for_each(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), [&data](const char c){ data.push_back(static_cast<uint32_t>(c)); });
		
		stream.close();

		return Shader(std::move(data), t);
	}

	Shader load_spirv_from_file(fString path)
	{
		fString fileExt(path, path.rfind('.', -4), -4, [](char c) { return std::tolower(c); });

		Shader::type type;

		if(fileExt == ".comp")		type = Shader::type::compute;
		else if(fileExt == ".vert") type = Shader::type::vertex;
		else if(fileExt == ".tesc") type = Shader::type::tesselation_control;
		else if(fileExt == ".tese") type = Shader::type::tesselation_evaluation;
		else if(fileExt == ".geom") type = Shader::type::geometry;
		else if(fileExt == ".frag") type = Shader::type::fragment;
		else Core::log::report(FATAL_ERROR, "Vulkan : unable to deduce the type of a shader from its extension (unrecognised shader extension : %s)", fileExt.c_str());

		return load_spirv_from_file(path, type);
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

	void Shader::destroy() noexcept
	{
		Ak_assert(_shader != VK_NULL_HANDLE, "trying to destroy an uninit shader");
		vkDestroyShaderModule(Render_Core::get().getDevice().get(), _shader, nullptr);

		for(auto& desc : _desc_sets)
			desc.destroy();

		Ak_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline layout");
		vkDestroyPipelineLayout(Render_Core::get().getDevice().get(), _pipelineLayout, nullptr);
	}
}
