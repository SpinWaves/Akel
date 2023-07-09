// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 09/07/2023

#include <Renderer/renderer_events.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/RenderPass/frame_buffer_library.h>

namespace Ak
{
    RendererComponent::RendererComponent(WindowComponent* window) : Component("__renderer_component" + std::to_string(_id)), _window(window)
	{
		_window->_renderer = _id;
		_fps.init();
		func::function<void(const BaseEvent&)> functor = [this](const BaseEvent& event){ this->_events_queue.push(event.what()); };
		EventBus::registerListener({ functor, "__renderer_component" + std::to_string(_id) });
		_id++;
	}

    void RendererComponent::onAttach()
    {
        Render_Core::get().init();

		_surface.create(*this);
		_cmd.init();
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_semaphores[i].init();
		_swapchain.init(this);

		_is_init = true;
    }

	bool RendererComponent::beginFrame()
	{
		_rendering_began = false;
		if(!_is_init)
			return false;
		_fps.setMaxFPS(_window->_window_has_focus ? _max_fps : 15);
		_fps.update();
		if(!_fps.makeRendering())
			return false;
		while(!_events_queue.empty())
		{
			if(_events_queue.front() == static_cast<uint32_t>(RenderEvents::resized))
				_framebufferResize = true;
			else if(_events_queue.front() == static_cast<uint32_t>(RenderEvents::quit))
			{
				onQuit();
				return false;
			}
			_events_queue.pop();
		}
		if(_framebufferResize)
		{
			_swapchain.recreate();
			return false;
		}
		auto device = Render_Core::get().getDevice().get();
		_cmd.getCmdBuffer(_active_image_index).waitForExecution();
		_cmd.getCmdBuffer(_active_image_index).reset();
		VkResult result = vkAcquireNextImageKHR(device, _swapchain(), UINT64_MAX, _semaphores[_active_image_index].getImageSemaphore(), VK_NULL_HANDLE, &_swapchain_image_index);
		if(result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			_swapchain.recreate();
			_framebufferResize = true;
			return false;
		}
		else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to acquire swapchain image");
		_cmd.getCmdBuffer(_active_image_index).beginRecord();
		_rendering_began = true;
		return true;
	}

	void RendererComponent::endFrame()
	{
		if(!_is_init)
			return;
		if(_framebufferResize)
			_framebufferResize = false;
		if(!_rendering_began)
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
		presentInfo.pImageIndices = &_swapchain_image_index;

		VkResult result = vkQueuePresentKHR(Render_Core::get().getQueue().getPresent(), &presentInfo);

		if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
			_framebufferResize = true;
		else if(result != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to present swap chain image");

		_active_image_index = (_active_image_index + 1) % MAX_FRAMES_IN_FLIGHT;
	}

    void RendererComponent::onQuit()
    {
		if(!_is_init)
			return;

        vkDeviceWaitIdle(Render_Core::get().getDevice().get());

		_cmd.destroy();

		_swapchain.destroy();
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_semaphores[i].destroy();
		_surface.destroy();
		_is_init = false;
    }
}
