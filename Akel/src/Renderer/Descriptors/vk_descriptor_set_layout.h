// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 30/05/2022

#ifndef __AK_VK_DESCRIPTOR_SET_LAYOUT__
#define __AK_VK_DESCRIPTOR_SET_LAYOUT__

#include <Akpch.h>
#include "descriptor.h"

namespace Ak
{
    class DescriptorSetLayout
    {
        public:
            enum class stage { vertex, fragment };
            void init(Desctype t = Desctype::uniform_buffer, size_t n = 1, stage s = stage::vertex);
            void destroy() noexcept;

            inline VkDescriptorSetLayout& operator()() noexcept { return _layout; }
            inline VkDescriptorSetLayout& get() noexcept { return _layout; }

        private:
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET_LAYOUT__
