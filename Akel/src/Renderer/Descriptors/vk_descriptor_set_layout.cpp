// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 20/02/2023

#include <Renderer/Descriptors/vk_descriptor_set_layout.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
    void DescriptorSetLayout::init(std::vector<std::pair<int, VkDescriptorType>> binds, VkShaderStageFlagBits stage)
    {
		/*
		std::vector<VkDescriptorBindingFlags> binding_flags(binds.size());
		for(int i = 0; i < binding_flags.size(); i++)
		{
			if(binds[i].second == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
				binding_flags[i] = VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT;
		}
		
		VkDescriptorSetLayoutBindingFlagsCreateInfo flags_info{};
		flags_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
		flags_info.bindingCount = binds.size();
		flags_info.pBindingFlags = binding_flags.data();
		*/
		std::vector<VkDescriptorSetLayoutBinding> bindings(binds.size());
		for(int i = 0; i < binds.size(); i++)
		{
			bindings[i].binding = binds[i].first;
			bindings[i].descriptorCount = 1;
			bindings[i].descriptorType = binds[i].second;
			bindings[i].pImmutableSamplers = nullptr;
			bindings[i].stageFlags = stage;
		}

		_bindings = std::move(binds);

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = _bindings.size();
        layoutInfo.pBindings = bindings.data();
		//layoutInfo.pNext = &flags_info;

        if(vkCreateDescriptorSetLayout(Render_Core::get().getDevice().get(), &layoutInfo, nullptr, &_layout) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create descriptor set layout");
    }

    void DescriptorSetLayout::destroy() noexcept
    {
        Ak_assert(_layout != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set layout");
        vkDestroyDescriptorSetLayout(Render_Core::get().getDevice().get(), _layout, nullptr);
    }
}
