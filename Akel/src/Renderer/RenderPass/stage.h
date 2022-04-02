// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 02/04/2022

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

			inline const std::vector<Attachment>& getAttachments() const noexcept { return _attachments; }
			inline const std::vector<SubpassType>& getSubpasses() const noexcept { return _subpasses; }

			inline Viewport& getViewport() noexcept { return _viewport; }
			inline void setViewport(const Viewport& viewport) noexcept { _viewport = viewport; }

			inline const RenderArea& getRenderArea() const noexcept { return _renderArea; }

			inline bool isOutOfDate() const noexcept { return _outOfDate; }

			inline const Renderpass* getRenderpass() const noexcept { return _renderpass.get(); }
			inline const ImageDepth* getDepthStencil() const noexcept { return _depthStencil.get(); }
			inline const Framebuffers* getFramebuffers() const noexcept { return _framebuffers.get(); }
			inline const std::vector<VkClearValue>& getClearValues() const noexcept { return _clearValues; }
			inline uint32_t getAttachmentCount(uint32_t subpass) const noexcept { return _subpassAttachmentCount[subpass]; }
			inline bool hasDepth() const noexcept { return _depthAttachment.has_value(); }
			inline bool hasSwapchain() const noexcept { return _swapchainAttachment.has_value(); }
			inline bool isMultisampled(uint32_t subpass) const noexcept { return _subpassMultisampled[subpass]; }

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
