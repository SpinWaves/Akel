// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#include <Renderer/Memory/allocator_GPU.h>
#include <Core/core.h>

namespace Ak
{
    Allocator_GPU::Allocator_GPU()
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if(vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create buffer");

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if(vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate buffer memory");

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    VkBuffer Allocator_GPU::allocBuffer(size_t size)
    {
        // TODO
    }

    Allocator_GPU::~Allocator_GPU()
    {
        // TODO
    }
}
