// This file is a part of AtlasEngine
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#ifndef __AE_VK_FRAMEBUFFER__
#define __AE_VK_FRAMEBUFFER__

#include <AEpch.h>

#include <Renderer/swapChain.h>

namespace AE
{
	class FrameBuffer : public SwapChain
	{
		public:
			FrameBuffer();
            void createFramebuffers();
            
			std::vector<VkImageView> swapChainImageViews;
	};
}

#endif // __AE_VK_FRAMEBUFFER__

