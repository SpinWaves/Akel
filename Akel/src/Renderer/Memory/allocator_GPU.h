// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_ALLOCATOR_GPU__
#define __AK_VULKAN_ALLOCATOR_GPU__

#include <Akpch.h>
#include <Renderer/Memory/globalBuffer.h>

namespace Ak
{
    class Allocator_GPU
    {
        public:
            explicit Allocator_GPU();

            GlobalBuffer& allocGBuffer(size_t size);
            void freeBuffer(GlobalBuffer& buffer);

            ~Allocator_GPU();

        private:
            VkBuffer _heap;
    };
}

#endif // __AK_VULKAN_ALLOCATOR_GPU__
