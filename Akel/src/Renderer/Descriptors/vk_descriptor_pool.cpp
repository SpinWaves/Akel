// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 08/12/2022

#include "vk_descriptor_pool.h"
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
    void DescriptorPool::init(std::size_t n, VkDescriptorPoolSize* size)
    {
        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = n;
        poolInfo.pPoolSizes = size;
        poolInfo.maxSets = 8192;

        if(vkCreateDescriptorPool(Render_Core::get().getDevice().get(), &poolInfo, nullptr, &_pool) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create descriptor pool");
    }

    void DescriptorPool::destroy() noexcept    
    {
        Ak_assert(_pool != VK_NULL_HANDLE, "trying to destroy an uninit descriptor pool");
        vkDestroyDescriptorPool(Render_Core::get().getDevice().get(), _pool, nullptr);
    }
}
