// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 07/02/2023

#include <Renderer/Descriptors/vk_descriptor_set_layout.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
    void DescriptorSetLayout::init(std::vector<std::pair<int, VkDescriptorType>> binds, VkShaderStageFlagBits stage)
    {
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

        if(vkCreateDescriptorSetLayout(Render_Core::get().getDevice().get(), &layoutInfo, nullptr, &_layout) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create descriptor set layout");
    }

    void DescriptorSetLayout::destroy() noexcept
    {
        Ak_assert(_layout != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set layout");
        vkDestroyDescriptorSetLayout(Render_Core::get().getDevice().get(), _layout, nullptr);
    }
}
