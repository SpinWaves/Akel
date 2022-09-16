// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 16/09/2022

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            void init(VkDescriptorType t = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, stid::size_t n = 1, int binding = 0, VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
