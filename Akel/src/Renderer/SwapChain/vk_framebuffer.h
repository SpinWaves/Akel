// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 04/04/2022

#ifndef __AK_VK_FRAMEBUFFER__
#define __AK_VK_FRAMEBUFFER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class FrameBuffer
    {
        public:
            void init(class SwapChain* swapchain, class ImageView& image);
            inline void destroy() noexcept { vkDestroyFramebuffer(Render_Core::get().getDevice()->get(), _framebuffer, nullptr); }

        private:
            VkFramebuffer _framebuffer;
    };
}

#endif // __AK_VK_FRAMEBUFFER__
