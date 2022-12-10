// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 11/12/2022

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

            VkDescriptorSet& operator()() noexcept;
            VkDescriptorSet& get() noexcept;

        private:
			VkDescriptorPool _pool = VK_NULL_HANDLE;
			std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> _desc_set;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET__
