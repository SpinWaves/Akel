// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 14/06/2023

#ifndef __AK_VK_RENDER_PASS__
#define __AK_VK_RENDER_PASS__

#include <Akpch.h>
#include <Renderer/Command/cmd_manager.h>

namespace Ak
{
	struct RenderPassAttachement
	{
		Image* image = nullptr;
		ImageType type = ImageType::other;

		RenderPassAttachement() = default;
		RenderPassAttachement(Image* i, ImageType it) : image(i), type(it) {}
	};

	struct RenderPassDesc
	{
		std::vector<RenderPassAttachement> attachements;
		bool clear = true;

		bool operator==(const RenderPassDesc& desc) noexcept;
	};

	class AK_API RenderPass
	{
		public:
			void init(RenderPassDesc desc);
			void destroy() noexcept;

			void begin(class CommandBuffer& cmd, std::array<float, 4> clears, class FrameBuffer& fb, uint32_t width, uint32_t height);
			void end(class CommandBuffer& cmd);

            inline VkRenderPass operator()() noexcept { return _renderPass; }
            inline VkRenderPass get() noexcept { return _renderPass; }

		private:
			VkRenderPass _renderPass = VK_NULL_HANDLE;
			std::vector<VkClearValue> _clears;
			bool _depth_only;
			bool _clear_depth;
			bool _is_running = false;
	};
}

#endif // __AK_VK_RENDER_PASS__
