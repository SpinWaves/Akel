// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 02/11/2023

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            void init(std::vector<std::pair<int, VkDescriptorType>> binds, VkShaderStageFlagBits stage);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }
			inline const std::vector<std::pair<int, VkDescriptorType>>& getBindings() const noexcept { return _bindings; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
			std::vector<std::pair<int, VkDescriptorType>> _bindings;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
