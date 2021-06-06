// This file is a part of Akel
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#ifndef __AK_VK_RENDERING__
#define __AK_VK_RENDERING__

#include <Akpch.h>
#include <Renderer/frameBuffer.h>

namespace Ak
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

#endif // __AK_VK_RENDERING__

