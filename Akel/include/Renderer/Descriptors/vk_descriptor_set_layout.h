// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 31/01/2023

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            void init(VkDescriptorType t, std::size_t n, int binding, VkShaderStageFlagBits stage);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }
			inline VkDescriptorType getType() noexcept { return _type; }
			inline int getBinding() noexcept { return _binding; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
			VkDescriptorType _type;
			int _binding = -1;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
