// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 16/06/2023

#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/RenderPass/vk_framebuffer.h>

namespace Ak
{
	void FrameBuffer::init(FrameBufferDesc& desc)
	{
		if(desc.render_pass.expired()) // this should be catched by the framebuffers library but just in case
			Core::log::report(FATAL_ERROR, "Vulkan : unable to create a new frame buffer, render pass pointer has expired");

		_desc = desc;
		std::vector<VkImageView> attachements;
		if(desc.mip_index >= 0)
		{
			_desc.width = desc.width >> desc.mip_index;
			_desc.height = desc.height >> desc.mip_index;
		}

		for(RenderPassAttachement& att : desc.attachements)
		{
			if(att.image != nullptr)
				attachements.push_back(att.image->getImageView());
		}

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = desc.render_pass.lock()->get();
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachements.size());
		framebufferInfo.pAttachments = attachements.data();
		framebufferInfo.width = desc.width;
		framebufferInfo.height = desc.height;
		framebufferInfo.layers = 1;

		if(vkCreateFramebuffer(Render_Core::get().getDevice().get(), &framebufferInfo, nullptr, &_framebuffer) != VK_SUCCESS)	
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a framebuffer");
	}

	void FrameBuffer::destroy() noexcept
	{
		Ak_assert(_framebuffer != VK_NULL_HANDLE, "trying to destroy an uninit FrameBuffer");
		vkDestroyFramebuffer(Render_Core::get().getDevice().get(), _framebuffer, nullptr);
		_framebuffer = VK_NULL_HANDLE;
	}
}
