// This file is a part of AtlasEngine
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#ifndef __AE_VK_RENDERING__
#define __AE_VK_RENDERING__

#include <AEpch.h>
#include <Renderer/frameBuffer.h>

namespace AE
{
	class Rendering : public FrameBuffer
	{
		public:
			Rendering();
            void createSemaphores();
            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            std::vector<VkFence> imagesInFlight;
            size_t currentFrame = 0;
	};
}

#endif // __AE_VK_RENDERING__

