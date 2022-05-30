// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 30/05/2022

#include "vk_descriptor_pool.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    void DescriptorPool::init(size_t n)
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = n;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        if(vkCreateDescriptorPool(Render_Core::get().getDevice().get(), &poolInfo, nullptr, &_pool) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create descriptor pool");
    }

    void DescriptorPool::destroy() noexcept    
    {
        Ak_assert(_pool != VK_NULL_HANDLE, "trying to destroy an uninit descriptor pool");
        vkDestroyDescriptorPool(Render_Core::get().getDevice().get(), _pool, nullptr);
    }
}
