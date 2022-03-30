// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_STAGE__
#define __AK_VK_STAGE__

#include "viewport.h"
#include "subPass.h"
#include "render_area.h"
#include "attachment.h"
#include "framebuffers.h"
#include "render_pass.h"
#include "swapchain.h"

namespace Ak
{
	class RenderStage
	{
		public:
			explicit RenderStage(std::vector<Attachment> images = {}, std::vector<SubpassType> subpasses = {}, const Viewport& viewport = Viewport());

			void update();
			void rebuild(const Swapchain& swapchain);

			std::optional<Attachment> getAttachment(const std::string& name) const;
			std::optional<Attachment> getAttachment(uint32_t binding) const;

			const Descriptor* getDescriptor(const std::string &name) const;
			const VkFramebuffer& getActiveFramebuffer(uint32_t activeSwapchainImage) const;

			const std::vector<Attachment>& getAttachments() const { return _attachments; }
			const std::vector<SubpassType>& getSubpasses() const { return _subpasses; }

			Viewport& getViewport() { return _viewport; }
			void setViewport(const Viewport& viewport) { _viewport = viewport; }

			const RenderArea& getRenderArea() const { return _renderArea; }

			bool isOutOfDate() const { return _outOfDate; }

			const Renderpass* getRenderpass() const { return _renderpass.get(); }
			const ImageDepth* getDepthStencil() const { return _depthStencil.get(); }
			const Framebuffers* getFramebuffers() const { return _framebuffers.get(); }
			const std::vector<VkClearValue>& getClearValues() const { return _clearValues; }
			uint32_t getAttachmentCount(uint32_t subpass) const { return _subpassAttachmentCount[subpass]; }
			bool hasDepth() const { return _depthAttachment.has_value(); }
			bool hasSwapchain() const { return _swapchainAttachment.has_value(); }
			bool isMultisampled(uint32_t subpass) const { return _subpassMultisampled[subpass]; }

		private:
			std::vector<Attachment> _attachments;
			std::vector<SubpassType> _subpasses;

			Viewport _viewport;

			std::unique_ptr<Renderpass> _renderpass;
			std::unique_ptr<ImageDepth> _depthStencil;
			std::unique_ptr<Framebuffers> _framebuffers;

			std::map<std::string, const Descriptor*> _descriptors;

			std::vector<VkClearValue> _clearValues;
			std::vector<uint32_t> _subpassAttachmentCount;
			std::optional<Attachment> _depthAttachment;
			std::optional<Attachment> _swapchainAttachment;
			std::vector<bool> _subpassMultisampled;

			RenderArea _renderArea;
			bool _outOfDate = false;
};
}

#endif // __AK_VK_STAGE__
