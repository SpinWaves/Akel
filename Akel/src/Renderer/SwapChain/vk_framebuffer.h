// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 08/05/2022

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

        private:
            VkFramebuffer _framebuffer = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_FRAMEBUFFER__
