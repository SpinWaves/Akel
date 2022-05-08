// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 08/05/2022

#ifndef __AK_VK_DESCRIPTOR_SET__
#define __AK_VK_DESCRIPTOR_SET__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Pipeline/vk_shader.h>

namespace Ak
{
    class DescriptorSet
    {
        public:
            void init(class UBO* ubo);
            void destroy() noexcept;

            inline VkDescriptorSet& operator()() noexcept { return _desc_set; }
            inline VkDescriptorSet& get() noexcept { return _desc_set; }

        private:
            VkDescriptorSet _desc_set = VK_NULL_HANDLE;
            Shader* _shader = nullptr;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET__
