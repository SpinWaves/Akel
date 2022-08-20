// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 20/08/2022

#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
	void FrameBuffer::init(SwapChain* swapchain, ImageView& image)
	{
		VkImageView attachments[] = { image() };

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = Render_Core::get().getRenderPass().get();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchain->_swapChainExtent.width;
		framebufferInfo.height = swapchain->_swapChainExtent.height;
		framebufferInfo.layers = 1;

		if(vkCreateFramebuffer(Render_Core::get().getDevice().get(), &framebufferInfo, nullptr, &_framebuffer) != VK_SUCCESS)	
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a framebuffer");
	}

	void FrameBuffer::destroy() noexcept
	{
	    Ak_assert(_framebuffer != VK_NULL_HANDLE, "trying to destroy an uninit FrameBuffer");
	    vkDestroyFramebuffer(Render_Core::get().getDevice().get(), _framebuffer, nullptr);
	}
}
