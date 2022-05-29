// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 29/05/2022

#include "vk_shader.h"
#include "vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>

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

	Shader::Shader(const std::vector<uint32_t> byte_code, Shader::type t) : _byte_code(std::move(byte_code)), _type(t) {}

	void Shader::generate()
	{
		SpvReflectShaderModule module = {};
		SpvReflectResult result = spvReflectCreateShaderModule(sizeof(k_sample_spv), k_sample_spv, &module);
		Ak_assert(result == SPV_REFLECT_RESULT_SUCCESS, "Renderer Shader : unable to create a Spir-V reflect shader module");

		uint32_t count = 0;
		result = spvReflectEnumerateDescriptorSets(&module, &count, nullptr);
		
		std::vector<SpvReflectDescriptorSet*> sets(count);
		result = spvReflectEnumerateDescriptorSets(&module, &count, sets.data());
		Ak_assert(result == SPV_REFLECT_RESULT_SUCCESS, "Renderer Shader : unable to enumerate descriptor sets");

		for(int i = 0; i < sets.size(); i++) // for some obscure reason range-based for loops don't want to compile with sets :/
		{
			auto set2 = spvReflectGetDescriptorSet(&module, sets[i]->set, &result);
			Ak_assert(result == SPV_REFLECT_RESULT_SUCCESS, "Renderer Shader : unable to get descriptor set");
			Ak_assert(sets[i] == set2, "Renderer Shader : somehting messed up while getting descripor set from a shader");

			for(int j = 0; j < sets[i]->binding_count; j++)
			{
				if(sets[i]->bindings[j]->descriptor_type == SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
				{
					_uniformBlocks.set_duet(sets[i]->bindings[j]->name, {sets[i]->bindings[j]->binding, sets[i]->bindings[j]->size});
				}
			}
		}

		spvReflectDestroyShaderModule(&module);

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
