// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_ALLOCATOR_GPU__
#define __AK_VULKAN_ALLOCATOR_GPU__

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
        bool operator==(const Buffer& buffer)
        {
            return memory == buffer.memory && offset == buffer.offset && size == buffer.size && free == buffer.free;
        }
    };

    class Allocator_GPU
    {
        public:
            explicit Allocator_GPU();

            Buffer allocBuffer(size_t size);
            void freeBuffer(const Buffer& buffer);

            ~Allocator_GPU();

        private:
            class Chunck : virtual private LowestInheritance
            {
                public:
                    explicit Chunck(VkDeviceSize size, int memoryTypeIndex);

                    bool alloc(VkDeviceSize size, const Buffer& buffer, VkDeviceSize alignment);
                    bool isIn(const Buffer& buffer) const;
                    void free(const Buffer& buffer);
                    int memoryTypeIndex() const { return _memoryTypeIndex; }

                private:
                    VkDeviceMemory _memory = VK_NULL_HANDLE;
                    VkDeviceSize _size;
                    int _memoryTypeIndex = 0;
                    std::vector<Buffer> _buffers;
                    void *_ptr = nullptr;
            };
    };
}

#endif // __AK_VULKAN_ALLOCATOR_GPU__
