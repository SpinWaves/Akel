// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_GPU_MEMORY_CHUNK__
#define __AK_VULKAN_GPU_MEMORY_CHUNK__

#include <Akpch.h>
#include <Renderer/lowestInheritance.h>

namespace Ak
{
    struct Buffer
    {
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkDeviceSize offset = 0;
        VkDeviceSize size = 0;
        bool free = true;
        void* ptr = nullptr;

        bool operator == (Buffer const& buffer);
    };

    class Chunk : virtual private LowestInheritance
    {
        public:
            explicit Chunk(VkDeviceSize size, int memoryTypeIndex);

            bool alloc(VkDeviceSize size, Buffer& buffer, VkDeviceSize alignment);
            bool isIn(const Buffer& buffer);
            void free(const Buffer& buffer);
            int memoryTypeIndex() const { return _memoryTypeIndex; }

        private:
            VkDeviceMemory _memory = VK_NULL_HANDLE;
            VkDeviceSize _size;
            int _memoryTypeIndex = 0;
            std::vector<Buffer> _buffers;
            void *_ptr = nullptr;
    };
}

#endif // __AK_VULKAN_GPU_MEMORY_CHUNK__
