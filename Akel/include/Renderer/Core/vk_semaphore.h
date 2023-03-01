// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 01/03/2023

#ifndef __AK_VK_GPU_SEMAPHORE__
#define __AK_VK_GPU_SEMAPHORE__

#include <Akpch.h>

namespace Ak
{
	class Semaphore
	{
		public:
			void init();
			void destroy() noexcept;

			inline VkSemaphore& getImageSemaphore(int i) noexcept { return _imageAvailableSemaphores[i]; }
			inline VkSemaphore& getRenderImageSemaphore(int i) noexcept { return _renderFinishedSemaphores[i]; }

		private:
			std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> _imageAvailableSemaphores;
			std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> _renderFinishedSemaphores;
	};
}

#endif // __AK_VK_GPU_SEMAPHORE__
