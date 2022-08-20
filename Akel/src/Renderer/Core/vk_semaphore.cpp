// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 20/08/2022

#include "vk_semaphore.h"
#include "render_core.h"
#include <Utils/assert.h>

namespace Ak
{
	void Semaphore::init()
	{
		_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		_imagesInFlight.resize(Render_Core::get().getSwapChain().getImagesNumber(), VK_NULL_HANDLE);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if(vkCreateSemaphore(Render_Core::get().getDevice().get(), &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(Render_Core::get().getDevice().get(), &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(Render_Core::get().getDevice().get(), &fenceInfo, nullptr, &_inFlightFences[i]) != VK_SUCCESS)
				Core::log::report(FATAL_ERROR, "Vulkan : failed to create synchronization objects for a frame");
		}
	}

	void Semaphore::destroy() noexcept
	{
		for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			Ak_assert(_renderFinishedSemaphores[i] != VK_NULL_HANDLE, "trying to destroy an uninit render semaphore");
			vkDestroySemaphore(Render_Core::get().getDevice().get(), _renderFinishedSemaphores[i], nullptr);

			Ak_assert(_imageAvailableSemaphores[i] != VK_NULL_HANDLE, "trying to destroy an uninit image semaphore");
			vkDestroySemaphore(Render_Core::get().getDevice().get(), _imageAvailableSemaphores[i], nullptr);
			
			Ak_assert(_inFlightFences[i] != VK_NULL_HANDLE, "trying to destroy an uninit fence");
			vkDestroyFence(Render_Core::get().getDevice().get(), _inFlightFences[i], nullptr);
		}
	}
}
