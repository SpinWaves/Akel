// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 20/02/2023

#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void FrameBuffer::init(RendererComponent& renderer, SwapChainImageView& image, VkImageView depth)
	{
		std::array<VkImageView, 2> attachments = {
			image(),
			depth
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderer.getRenderPass().get();
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = renderer.getSwapChain()._swapChainExtent.width;
		framebufferInfo.height = renderer.getSwapChain()._swapChainExtent.height;
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
