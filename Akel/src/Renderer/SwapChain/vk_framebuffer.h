// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 09/05/2022

#ifndef __AK_VK_FRAMEBUFFER__
#define __AK_VK_FRAMEBUFFER__

#include <Akpch.h>

namespace Ak
{
    class FrameBuffer
    {
        public:
            void init(class SwapChain* swapchain, class ImageView& image);
            void destroy() noexcept;

            inline VkFramebuffer& operator()() noexcept { return _framebuffer; }
            inline VkFramebuffer& get() noexcept { return _framebuffer; }

        private:
            VkFramebuffer _framebuffer = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_FRAMEBUFFER__
