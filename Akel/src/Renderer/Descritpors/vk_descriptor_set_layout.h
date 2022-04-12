// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 12/04/2022

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            void init();
            inline void destroy()
            {
                static_assert(_layout != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set layout");
                vkDestroyDescriptorSetLayout(Render_Core::get().getDevice().get(), _layout, nullptr);
            }

            inline VkDescriptorSetLayout& operator()() const { return _layout; }
            inline VkDescriptorSetLayout& get() const { return _layout; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
