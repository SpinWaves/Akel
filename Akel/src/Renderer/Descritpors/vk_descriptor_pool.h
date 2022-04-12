// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 12/04/2022

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
                static_assert(_pool != VK_NULL_HANDLE, "trying to destroy an uninit descriptor pool");
                vkDestroyDescriptorPool(Render_Core::get().getDevice().get(), _pool, nullptr);
            }

            inline VkDescriptorPool& operator()() const { return _pool; }
            inline VkDescriptorPool& get() const { return _pool; }

        private:
            VkDescriptorPool _pool = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_POOL__
