// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 16/09/2022

#include "vk_descriptor_set_layout.h"
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
    void DescriptorSetLayout::init(VkDescriptorType t, std::size_t n, int binding, VkShaderStageFlagBits stage)
    {
        VkDescriptorSetLayoutBinding binding{};
        binding.binding = binding;
        binding.descriptorCount = 1;
        binding.descriptorType = t;
        binding.pImmutableSamplers = nullptr;
        binding.stageFlags = stage;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = n;
        layoutInfo.pBindings = &binding;

        if(vkCreateDescriptorSetLayout(Render_Core::get().getDevice().get(), &layoutInfo, nullptr, &_layout) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create descriptor set layout");
    }

    void DescriptorSetLayout::destroy() noexcept
    {
        Ak_assert(_layout != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set layout");
        vkDestroyDescriptorSetLayout(Render_Core::get().getDevice().get(), _layout, nullptr);
    }
}
