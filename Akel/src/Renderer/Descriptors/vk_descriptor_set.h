// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 08/12/2022

#ifndef __AK_VK_DESCRIPTOR_SET__
#define __AK_VK_DESCRIPTOR_SET__

#include <Akpch.h>

namespace Ak
{
    class DescriptorSet
    {
        public:
            void init(class UBO* ubo, class DescriptorSetLayout& layout, class DescriptorPool& pool);
            void destroy() noexcept;

            inline VkDescriptorSet& operator()() noexcept { return _desc_set; }
            inline VkDescriptorSet& get() noexcept { return _desc_set; }

        private:
			VkDescriptorPool _pool = VK_NULL_HANDLE;
            VkDescriptorSet _desc_set = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET__
