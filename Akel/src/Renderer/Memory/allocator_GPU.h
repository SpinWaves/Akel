// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_ALLOCATOR_GPU__
#define __AK_VULKAN_ALLOCATOR_GPU__

#include <Akpch.h>
#include <Renderer/Memory/chunk.h>

namespace Ak
{
    class Allocator_GPU
    {
        public:
            explicit Allocator_GPU();

            Buffer allocBuffer(size_t size);
            void freeBuffer(const Buffer& buffer);

            ~Allocator_GPU();

        private:
    };
}

#endif // __AK_VULKAN_ALLOCATOR_GPU__
