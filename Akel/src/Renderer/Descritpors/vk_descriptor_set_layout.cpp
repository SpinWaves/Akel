// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 29/04/2022

#include "vk_descriptor_set_layout.h"

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
            case DescriptorSetLayout::type::uniform_buffer_dynamique : binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC; break;
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
}
