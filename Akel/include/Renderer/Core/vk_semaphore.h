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

			inline VkSemaphore& getImageSemaphore() noexcept { return _imageAvailableSemaphores; }
			inline VkSemaphore& getRenderImageSemaphore() noexcept { return _renderFinishedSemaphores; }

		private:
			VkSemaphore _imageAvailableSemaphores = VK_NULL_HANDLE;
			VkSemaphore _renderFinishedSemaphores = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_GPU_SEMAPHORE__
