// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 14/06/2023

#ifndef __AK_VK_FRAMEBUFFER__
#define __AK_VK_FRAMEBUFFER__

#include <Akpch.h>

namespace Ak
{
	struct AK_API FrameBufferDesc
	{

	};

    class AK_API FrameBuffer
    {
        public:
            void init(class RendererComponent& renderer, class SwapChainImageView& image, VkImageView depth);
            void destroy() noexcept;

            inline VkFramebuffer operator()() noexcept { return _framebuffer; }
            inline VkFramebuffer get() noexcept { return _framebuffer; }

        private:
            VkFramebuffer _framebuffer = VK_NULL_HANDLE;
    };
}

#endif // __AK_VK_FRAMEBUFFER__
