// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 08/05/2022

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            enum class type { uniform_buffer, dynamic_uniform_buffer, image_sampler };

            void init(type t = type::uniform_buffer);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
