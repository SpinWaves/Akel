// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 30/01/2023

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            void init(VkDescriptorType t = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, std::size_t n = 1, int binding = 0, VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }
			inline VkDescriptorType getType() noexcept { return _type; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
			VkDescriptorType _type;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
