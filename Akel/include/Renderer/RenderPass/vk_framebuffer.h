// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 15/06/2023

#ifndef __AK_VK_FRAMEBUFFER__
#define __AK_VK_FRAMEBUFFER__

#include <Akpch.h>
#include <Renderer/RenderPass/vk_render_pass.h>

namespace Ak
{
	struct AK_API FrameBufferDesc
	{
		std::vector<RenderPassAttachement> attachements;
		std::weak_ptr<RenderPass> render_pass;
		uint32_t width;
		uint32_t height;
		uint32_t layer = 1;
		uint32_t msaa_level = 0;
		int mip_index = 0;
		bool screen_fbo = false;
	};

	class AK_API FrameBuffer
	{
		public:
			void init(FrameBufferDesc& desc);
			void destroy() noexcept;

			inline VkFramebuffer operator()() noexcept { return _framebuffer; }
			inline VkFramebuffer get() noexcept { return _framebuffer; }

			inline uint32_t getWidth() const noexcept { return _width; }
			inline uint32_t getHeight() const noexcept { return _height; }

		private:
			VkFramebuffer _framebuffer = VK_NULL_HANDLE;
			uint32_t _width = 0;
			uint32_t _height = 0;
	};
}

#endif // __AK_VK_FRAMEBUFFER__
