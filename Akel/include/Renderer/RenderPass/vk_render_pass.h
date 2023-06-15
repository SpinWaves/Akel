// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 15/06/2023

#ifndef __AK_VK_RENDER_PASS__
#define __AK_VK_RENDER_PASS__

#include <Akpch.h>
#include <Renderer/Command/cmd_manager.h>
#include <Renderer/Images/vk_image.h>

namespace Ak
{
	struct RenderPassAttachement
	{
		Image* image = nullptr;
		ImageType type = ImageType::other;

		RenderPassAttachement() = default;
		RenderPassAttachement(Image* i, ImageType it) : image(i), type(it) {}
		inline bool operator==(const RenderPassAttachement& rhs) const noexcept { return image == rhs.image && type == rhs.type; }
	};

	struct RenderPassDesc
	{
		std::vector<RenderPassAttachement> attachements;
		bool clear = true;

		inline bool operator==(const RenderPassDesc& desc) const noexcept { return clear == desc.clear && attachements == desc.attachements; }
	};

	class AK_API RenderPass
	{
		public:
			RenderPass() = default;

			void init(RenderPassDesc desc);
			void destroy() noexcept;

			void begin(class CmdBuffer& cmd, std::array<float, 4> clears, class FrameBuffer& fb, uint32_t width, uint32_t height);
			void end(class CmdBuffer& cmd);

            inline VkRenderPass operator()() noexcept { return _renderPass; }
            inline VkRenderPass get() noexcept { return _renderPass; }

			~RenderPass() = default;

		private:
			VkRenderPass _renderPass = VK_NULL_HANDLE;
			std::vector<VkClearValue> _clears;
			bool _depth_only;
			bool _clear_depth;
			bool _is_running = false;
	};
}

#endif // __AK_VK_RENDER_PASS__
