// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 01/03/2023

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent(WindowComponent* window) : Component("__renderer_component"), _window(window)
	{
		_window->_renderer = this;
	}

    void RendererComponent::onAttach()
    {
        Render_Core::get().init();
		
		_surface.create(*this);
		_swapchain.init(this);
		_pass.init(this);
		_swapchain.initFB();
		_cmd.init();
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_semaphores[i].init();

		_is_init = true;
		getMainAppProjectFile().setBoolValue("__renderer_component", true);
    }

	bool RendererComponent::beginFrame()
	{
		if(!_is_init)
			return false;

		auto device = Render_Core::get().getDevice().get();

		_cmd.getCmdBuffer(_active_image_index).waitForExecution();
		_cmd.getCmdBuffer(_active_image_index).reset();

		VkResult result = vkAcquireNextImageKHR(device, _swapchain(), UINT64_MAX, _semaphores[_active_image_index].getImageSemaphore(), VK_NULL_HANDLE, &_image_index);

		if(result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			_swapchain.recreate();
			return false;
		}
		else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to acquire swapchain image");

		_cmd.getCmdBuffer(_active_image_index).beginRecord();

		return true;
	}

	void RendererComponent::endFrame()
	{
		if(!_is_init)
			return;

		_cmd.getCmdBuffer(_active_image_index).endRecord();

		_cmd.getCmdBuffer(_active_image_index).submit(_semaphores[_active_image_index]);

		VkSwapchainKHR swapchain = _swapchain();
		VkSemaphore signalSemaphores[] = { _semaphores[_active_image_index].getRenderImageSemaphore() };

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain;
		presentInfo.pImageIndices = &_image_index;

		VkResult result = vkQueuePresentKHR(Render_Core::get().getQueue().getPresent(), &presentInfo);

		if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized)
		{
			_framebufferResized = false;
			_swapchain.recreate();
		}
		else if(result != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to present swap chain image");

		_active_image_index = (_active_image_index + 1) % MAX_FRAMES_IN_FLIGHT;
	}

    void RendererComponent::onQuit()
    {
		if(!_is_init)
			return;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

        vkDeviceWaitIdle(Render_Core::get().getDevice().get());

		_cmd.destroy();

		_swapchain.destroyFB();
		_pass.destroy();
		_swapchain.destroy();
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_semaphores[i].destroy();
		_surface.destroy();
		_is_init = false;
    }
}
