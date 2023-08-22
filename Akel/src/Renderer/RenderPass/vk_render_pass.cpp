// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 22/08/2023

#include <Renderer/Images/vk_image.h>
#include <Renderer/RenderPass/vk_render_pass.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	VkAttachmentDescription GetAttachmentDescription(ImageType type, Image* image, bool clear = true)
	{
		VkAttachmentDescription attachement{};

		if(type == ImageType::color)
		{
			attachement.format = image->getFormat();
			attachement.initialLayout = image->getLayout();
			attachement.finalLayout = attachement.initialLayout;
		}
		else if(type == ImageType::cube)
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported (yet) image type '%d'", static_cast<int>(type));
			return attachement;
		}
		else if(type == ImageType::depth)
		{
			attachement.format = image->getFormat();
			attachement.initialLayout = image->getLayout();
			attachement.finalLayout = attachement.initialLayout;
		}
		else if(type == ImageType::depth_array)
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported (yet) image type '%d'", static_cast<int>(type));
			return attachement;
		}
		else
		{
			Core::log::report(ERROR, "Vulkan Render Pass Attachement Description : unsupported image type '%d'", static_cast<int>(type));
			return attachement;
		}

		if(clear)
		{
			attachement.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachement.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachement.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}
		else
		{
			attachement.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			attachement.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		}

		attachement.samples = VK_SAMPLE_COUNT_1_BIT;
		attachement.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachement.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachement.flags = 0;

		return attachement;
	}

	void RenderPass::init(RenderPassDesc desc)
	{
		std::vector<VkAttachmentDescription> attachements;

		std::vector<VkAttachmentReference> colorAttachementReferences;
		std::vector<VkAttachmentReference> depthAttachementReferences;

		_depth_only  = true;
		_clear_depth = false;

		for(uint32_t i = 0; i < desc.attachements.size(); i++)
		{
			attachements.push_back(GetAttachmentDescription(desc.attachements[i].type, desc.attachements[i].image, desc.clear));

			if(desc.attachements[i].type == ImageType::color)
			{
				VkImageLayout layout = desc.attachements[i].image->getLayout();
				VkAttachmentReference colorAttachementRef{};
				colorAttachementRef.attachment = i;
				colorAttachementRef.layout = layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL : layout;
				colorAttachementReferences.push_back(colorAttachementRef);
				_depth_only = false;
			}
			else if(desc.attachements[i].type == ImageType::depth)
			{
				VkAttachmentReference depthAttachementRef{};
				depthAttachementRef.attachment = i;
				depthAttachementRef.layout = desc.attachements[i].image->getLayout();
				depthAttachementReferences.push_back(depthAttachementRef);
				_clear_depth = desc.clear;
			}
		}

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = colorAttachementReferences.size();
		subpass.pColorAttachments = colorAttachementReferences.data();
		subpass.pDepthStencilAttachment = depthAttachementReferences.data();

		VkRenderPassCreateInfo renderPassCreateInfo{};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = desc.attachements.size();
		renderPassCreateInfo.pAttachments = attachements.data();
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;
		renderPassCreateInfo.dependencyCount = 0;
		renderPassCreateInfo.pDependencies = nullptr;

		if(vkCreateRenderPass(Render_Core::get().getDevice().get(), &renderPassCreateInfo, nullptr, &_renderPass) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create render pass");

		_clears.resize(desc.attachements.size());
		Core::log::report(DEBUGLOG, "Vulkan : created new renderpass");
	}

	void RenderPass::begin(CmdBuffer& cmd, std::array<float, 4> clears, FrameBuffer& fb, uint32_t width, uint32_t height)
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
		renderPassInfo.framebuffer = fb.get();
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = { width, height };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(_clears.size());
		renderPassInfo.pClearValues = _clears.data();

		vkCmdBeginRenderPass(cmd.get(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		_is_running = true;
	}

	void RenderPass::end(CmdBuffer& cmd)
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
