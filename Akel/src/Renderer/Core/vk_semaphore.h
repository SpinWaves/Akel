// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_SEMAPHORE__
#define __AK_VK_SEMAPHORE__

#include <Akpch.h>
#include "render_core.h"

namespace Ak
{
	class Semaphore
	{
		public:
			void init();
			void destroy() noexcept;

			inline VkSemaphore& getImageSemaphore(int i) noexcept { return _imageAvailableSemaphores[i]; }
			inline VkSemaphore& getRenderImageSemaphore(int i) noexcept { return _renderFinishedSemaphores[i]; }
			inline VkFence& getInFlightFence(int i) noexcept { return _inFlightFences[i]; }
			inline VkFence& getInFlightImage(int i) noexcept { return _imagesInFlight[i]; }

		private:
			std::vector<VkSemaphore> _imageAvailableSemaphores;
			std::vector<VkSemaphore> _renderFinishedSemaphores;
			std::vector<VkFence> _inFlightFences;
			std::vector<VkFence> _imagesInFlight;
	};
}

#endif // __AK_VK_SEMAPHORE__
