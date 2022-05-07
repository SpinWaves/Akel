// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            enum class type { uniform_buffer, dynamique_uniform_buffer, image_sampler };

            void init(type t = type::uniform_buffer);
            inline void destroy()
            {
                Ak_assert(_layout != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set layout");
                vkDestroyDescriptorSetLayout(Render_Core::get().getDevice().get(), _layout, nullptr);
            }

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
