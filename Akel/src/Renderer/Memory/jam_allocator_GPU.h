// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 10/12/2021

#ifndef __AK_VULKAN_JAMALLOCATOR_GPU__
#define __AK_VULKAN_JAMALLOCATOR_GPU__

#include <Akpch.h>
#include <Renderer/Memory/chunk.h>

namespace Ak
{
    class JamAllocator_GPU
    {
        public:
            explicit Allocator_GPU();

            Buffer& allocBuffer(VkDeviceSize size);
            inline bool canHold(VkDeviceSize size);
            inline bool contains(Buffer& buffer);
            void freeBuffer(const Buffer& buffer);

            ~Allocator_GPU();

        private:
            std::vector<Chunk> _chuncks;
    };
}

#endif // __AK_VULKAN_JAMALLOCATOR_GPU__
