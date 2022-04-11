// this file is a part of akel
// authors : @kbz_8
// created : 10/04/2022
// updated : 11/04/2022

#include "vk_render_pass.h"

namespace Ak
{
	void RenderPass::init()
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;

		if(vkCreateRenderPass(Render_Core::get().getDevice().get(), &renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create render pass");
	}

	void RenderPass::begin()
	{
		if(_is_running)
			return;

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = Render_Core::get().getSwapChain()._framebuffers[Render_Core::get().getActiveImageIndex()];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = Render_Core::get().getSwapChain()._swapChainExtent;

		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &Render_Core::get().getClearValue();
		vkCmdBeginRenderPass(Render_Core::get().getCmdBuffer().get(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		_is_running = true;
	}

	void RenderPass::end()
	{
		if(!_is_running)
			return;

		vkCmdEndRenderPass(Render_Core::get().getCmdBuffer().get());
		_is_running = false;
	}
}
