// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 09/05/2022

#include "vk_descriptor_set_layout.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    void DescriptorSetLayout::init(DescriptorSetLayout::type t)
    {
        VkDescriptorSetLayoutBinding binding{};
        binding.binding = 0;
        binding.descriptorCount = 1;
        
        switch(t)
        {
            case DescriptorSetLayout::type::uniform_buffer : binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;
            case DescriptorSetLayout::type::dynamic_uniform_buffer : binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; break;
            case DescriptorSetLayout::type::image_sampler : binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; break;
        }
        
        binding.pImmutableSamplers = nullptr;
        binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
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
