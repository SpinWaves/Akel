// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 18/09/2022

#ifndef __AK_VK_DESCRIPTOR_POOL__
#define __AK_VK_DESCRIPTOR_POOL__

#include <Akpch.h>

namespace Ak
{
    class DescriptorPool
    {
        public:
            void init(std::size_t n, VkDescriptorPoolSize size);
            void destroy() noexcept;

            inline VkDescriptorPool& operator()() noexcept { return _pool; }
            inline VkDescriptorPool& get() noexcept { return _pool; }

			inline VkDescriptorPoolSize getSize() const noexcept { _size; }

        private:
			VkDescriptorPoolSize _size;
            VkDescriptorPool _pool = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_POOL__
