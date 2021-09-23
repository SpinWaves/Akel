// This file is a part of Akel
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#ifndef __AK_VK_FRAMEBUFFER__
#define __AK_VK_FRAMEBUFFER__

#include <Akpch.h>

#include <Renderer/swapChain.h>

namespace Ak
{
	class FrameBuffer : public SwapChain
	{
		public:
			FrameBuffer();
            void createFramebuffers();
            
			std::vector<VkImageView> swapChainImageViews;
	};
}

#endif // __AK_VK_FRAMEBUFFER__
