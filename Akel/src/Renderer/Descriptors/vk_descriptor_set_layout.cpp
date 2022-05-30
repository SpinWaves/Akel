// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 30/05/2022

#include "vk_descriptor_set_layout.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    void DescriptorSetLayout::init(Desctype t, size_t n, DescriptorSetLayout::stage s)
    {
        VkDescriptorSetLayoutBinding binding{};
        binding.binding = 0;
        binding.descriptorCount = 1;
        
        switch(t)
        {
            case Desctype::uniform_buffer : binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;
            case Desctype::dynamic_uniform_buffer : binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; break;
            case Desctype::image_sampler : binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; break;
        }
        
        binding.pImmutableSamplers = nullptr;
        binding.stageFlags = s == DescriptorSetLayout::stage::vertex ? VK_SHADER_STAGE_VERTEX_BIT : VK_SHADER_STAGE_FRAGMENT_BIT;

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
