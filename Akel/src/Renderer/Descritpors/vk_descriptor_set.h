// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 12/04/2022

#ifndef __AK_VK_DESCRIPTOR_SET__
#define __AK_VK_DESCRIPTOR_SET__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class DescriptorSet
    {
        public:
            void init();
            inline void destroy()
            {
                static_assert(_desc_set != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set");
                vkFreeDescriptorSets(Render_Core::get().getDevice().get(), Render_Core::get().getDescPool().get(), 1, &_desc_set);
            }

            inline VkDescriptorSet& operator()() const { return _desc_set; }
            inline VkDescriptorSet& get() const { return _desc_set; }

        private:
            VkDescriptorSet _desc_set = VK_NULL_HANDLE;
            VkDescriptorSetLayout _layout = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET__
