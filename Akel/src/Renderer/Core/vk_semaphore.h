// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 10/04/2022

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
			void destroy() noexcept
			{
				for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
				{
					static_assert(_renderFinishedSemaphores[i] != VK_NULL_HANDLE, "trying to destroy an uninit render semaphore");
					vkDestroySemaphore(Render_Core::get().getDevice().get(), _renderFinishedSemaphores[i], nullptr);

					static_assert(_imageAvailableSemaphores[i] != VK_NULL_HANDLE, "trying to destroy an uninit image semaphore");
					vkDestroySemaphore(Render_Core::get().getDevice().get(), _imageAvailableSemaphores[i], nullptr);
					
					static_assert(_inFlightFences[i] != VK_NULL_HANDLE, "trying to destroy an uninit fence");
					vkDestroyFence(Render_Core::get().getDevice().get(), _inFlightFences[i], nullptr);
				}
			}

			inline VkSemaphore& getImageSemaphore(int i) const noexcept { return _imageAvailableSemaphores[i]; }
			inline VkSemaphore& getRenderImageSemaphore(int i) const noexcept { return _renderFinishedSemaphores[i]; }
			inline VkFence& getInFlightFence(int i) const noexcept { return _inFlightFences[i]; }
			inline VkFence& getInFlightImage(int i) const noexcept { return _imagesInFlight[i]; }

		private:
			std::vector<VkSemaphore> _imageAvailableSemaphores;
			std::vector<VkSemaphore> _renderFinishedSemaphores;
			std::vector<VkFence> _inFlightFences;
			std::vector<VkFence> _imagesInFlight;
	};
}

#endif // __AK_VK_SEMAPHORE__
