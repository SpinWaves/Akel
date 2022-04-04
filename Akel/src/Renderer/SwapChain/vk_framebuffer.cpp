// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 04/04/2022

#include "vk_swapchain.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	void FrameBuffer::init(SwapChain* swapchain, ImageView& image)
	{
		VkImageView attachments[] = { image() };

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = Render_Core::get().getRenderPass()->get();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchain->swapChainExtent.width;
		framebufferInfo.height = swapchain->swapChainExtent.height;
		framebufferInfo.layers = 1;

		if(vkCreateFramebuffer(Render_Core::get().getDevice()->get(), &framebufferInfo, nullptr, &_framebuffer) != VK_SUCCESS)	
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a framebuffer");
	}
}
