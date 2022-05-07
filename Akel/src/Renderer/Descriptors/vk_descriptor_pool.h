// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_DESCRIPTOR_POOL__
#define __AK_VK_DESCRIPTOR_POOL__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class DescriptorPool
    {
        public:
            void init();
            inline void destroy()
            {
                Ak_assert(_pool != VK_NULL_HANDLE, "trying to destroy an uninit descriptor pool");
                vkDestroyDescriptorPool(Render_Core::get().getDevice().get(), _pool, nullptr);
            }

            inline VkDescriptorPool& operator()() noexcept { return _pool; }
            inline VkDescriptorPool& get() noexcept { return _pool; }

        private:
            VkDescriptorPool _pool = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_POOL__
