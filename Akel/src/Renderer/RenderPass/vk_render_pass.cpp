// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 14/06/2023

#include <Renderer/Images/vk_image.h>
#include <Renderer/RenderPass/vk_render_pass.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	bool RenderPassDesc::operator==(const RenderPassDesc& desc) noexcept
	{
		return clear == desc.clear && attachment == desc.attachment;
	}

	VkAttachmentDescription GetAttachmentDescription(ImageType type, Image* image, bool clear = true)
	{
		VkAttachmentDescription attachment{};

		if(type == ImageType::color)
		{
			attachment.format = image->getFormat();
			attachment.initialLayout = image->getLayout();
			attachment.finalLayout = attachment.initialLayout;
		}
		else if(type == ImageType::cube)
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported (yet) image type '%d'", static_cast<int>(type));
			return attachment;
		}
		else if(type == ImageType::depth)
		{
			attachment.format = image->getFormat();
			attachment.initialLayout = image->getLayout();
			attachment.finalLayout = attachment.initialLayout;
		}
		else if(type == ImageType::depth_array)
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported (yet) image type '%d'", static_cast<int>(type));
			return attachment;
		}
		else
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported image type '%d'", static_cast<int>(type));
			return attachment;
		}

		if(clear)
		{
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}
		else
		{
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		}

		attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.flags = 0;

		return attachment;
	}

	void RenderPass::init(RenderPassDesc desc)
	{
		std::vector<VkAttachmentDescription> attachments;

		std::vector<VkAttachmentReference> colourAttachmentReferences;
		std::vector<VkAttachmentReference> depthAttachmentReferences;

		_depth_only  = true;
		_clear_depth = false;

		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = renderer->getSwapChain()._swapChainImageFormat;
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

		VkFormat depth_format = findSupportedFormat({VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );

		VkAttachmentDescription depthAttachment{};
		depthAttachment.format = depth_format;
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthAttachmentRef{};
		depthAttachmentRef.attachment = 1;
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

		if(vkCreateRenderPass(Render_Core::get().getDevice().get(), &renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create render pass");
	}

	void RenderPass::begin(CommandBuffer& cmd, std::array<float, 4> clears, FrameBuffer& fb, uint32_t width, uint32_t height)
	{
		if(_is_running)
			return;

		if(!_depth_only)
		{
			for(int i = 0; i < _clears.size(); i++)
			{
				_clears[i].color.float32[0] = clears[0];
				_clears[i].color.float32[1] = clears[1];
				_clears[i].color.float32[2] = clears[2];
				_clears[i].color.float32[3] = clears[3];
			}
		}

		if(_clear_depth)
			_clears.back().depthStencil = VkClearDepthStencilValue{ 1.0f, 0 };

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = _renderPass;
		renderPassInfo.framebuffer = fdb.get();
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = { width, height };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(_clears.size());
		renderPassInfo.pClearValues = _clears.data();

		vkCmdBeginRenderPass(cmd.get(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		_is_running = true;
	}

	void RenderPass::end(CommandBuffer& cmd)
	{
		if(!_is_running)
			return;

		vkCmdEndRenderPass(cmd.get());
		_is_running = false;
	}

	void RenderPass::destroy() noexcept
	{
		Ak_assert(_renderPass != VK_NULL_HANDLE, "trying to destroy an uninit render pass");
		vkDestroyRenderPass(Render_Core::get().getDevice().get(), _renderPass, nullptr);
	}
}
