// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2022
// Updated : 28/03/2022

#ifndef __AK_VK_FRAMEBUFFERS__
#define __AK_VK_FRAMEBUFFERS__

#include <Akpch.h>
#include <Utils/nonCopyable.h>
#include "swapchain.h"

namespace Ak
{
	class ImageDepth;
	class Renderpass;
	class RenderStage;

	class Framebuffers : public non_copyable
	{
		public:
			Framebuffers(const Vector2ui& extent, const RenderStage& renderStage, const Renderpass& renderPass, const Swapchain& swapchain, const ImageDepth& depthStencil,
				VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT);

			Image2d* getAttachment(uint32_t index) const { return imageAttachments[index].get(); }

			const std::vector<std::unique_ptr<Image2d>>& getImageAttachments() const noexcept { return imageAttachments; }
			const std::vector<VkFramebuffer>& getFramebuffers() const noexcept { return framebuffers; }
			
			~Framebuffers();

		private:
			std::vector<std::unique_ptr<Image2d>> imageAttachments;
			std::vector<VkFramebuffer> framebuffers;
		};
}

#endif // __AK_VK_FRAMEBUFFERS__
