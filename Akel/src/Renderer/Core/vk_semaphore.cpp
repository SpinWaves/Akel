// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 01/03/2023

#include <Renderer/Core/vk_semaphore.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void Semaphore::init()
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if(	vkCreateSemaphore(Render_Core::get().getDevice().get(), &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(Render_Core::get().getDevice().get(), &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != VK_SUCCESS)
					Core::log::report(FATAL_ERROR, "Vulkan : failed to create GPU synchronization objects for a frame");
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
		}
	}
}
