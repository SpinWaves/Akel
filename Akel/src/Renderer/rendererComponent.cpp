// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 16/02/2023

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
		_semaphore.init(*this);

		_is_init = true;
		getMainAppProjectFile().setBoolValue("__renderer_component", true);
    }

	bool RendererComponent::beginFrame()
	{
		if(!_is_init)
			return false;

		auto device = Render_Core::get().getDevice().get();

		vkWaitForFences(device, 1, &_semaphore.getInFlightFence(_active_image_index), VK_TRUE, UINT64_MAX);

		_image_index = 0;
		VkResult result = vkAcquireNextImageKHR(device, _swapchain(), UINT64_MAX, _semaphore.getImageSemaphore(_active_image_index), VK_NULL_HANDLE, &_image_index);

		if(result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			_swapchain.recreate();
			return false;
		}
		else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to acquire swapchain image");

		vkResetFences(device, 1, &_semaphore.getInFlightFence(_active_image_index));

		return true;
	}

	void RendererComponent::endFrame()
	{
		if(!_is_init)
			return;

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { _semaphore.getImageSemaphore(_active_image_index) };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_cmd.getCmdBuffer(_active_image_index).get();

		VkSemaphore signalSemaphores[] = { _semaphore.getRenderImageSemaphore(_active_image_index) };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if(vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &submitInfo, _semaphore.getInFlightFence(_active_image_index)) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to submit draw command buffer");

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &_swapchain();

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
		_semaphore.destroy();
		_surface.destroy();
		_is_init = false;
    }
}
