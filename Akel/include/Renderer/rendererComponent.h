// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 21/12/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include "Pipeline/vk_shader.h"
#include "Pipeline/vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>

#include <Renderer/Core/vk_surface.h>
#include <Renderer/Core/vk_semaphore.h>
#include <Renderer/Command/vk_cmd_pool.h>
#include <Renderer/Command/vk_cmd_buffer.h>
#include <Renderer/SwapChain/vk_swapchain.h>
#include <Renderer/SwapChain/vk_render_pass.h>

namespace Ak
{
	class RendererComponent : public Component
	{
		public:
			RendererComponent(WindowComponent* window);

			void onAttach() override;

			bool beginFrame();
			void endFrame();

			inline WindowComponent* getWindow() noexcept { return _window; }
			inline void setWindow(WindowComponent* window) noexcept { _window = window; }

			inline Surface& getSurface() noexcept { return _surface; }
			inline CmdPool& getCmdPool() noexcept { return _cmd_pool; }
			inline SwapChain& getSwapChain() noexcept { return _swapchain; }
			inline Semaphore& getSemaphore() noexcept { return _semaphore; }
			inline RenderPass& getRenderPass() noexcept { return _pass; }
			inline VkClearValue& getClearValue() noexcept { return _clearColor; }
			inline CmdBuffer& getCmdBuffer(int i) noexcept { return _cmd_buffers[i]; }
			inline CmdBuffer& getActiveCmdBuffer() noexcept { return _cmd_buffers[_active_image_index]; }
			inline uint32_t getActiveImageIndex() const noexcept { return _active_image_index; }
			inline uint32_t getImageIndex() const noexcept { return _image_index; }
			inline bool isInit() const noexcept { return _is_init; }

			inline constexpr void requireFrameBufferResize() noexcept { _framebufferResized = true; }
			inline bool isFrameBufferResizeRequested() const noexcept { return _framebufferResized; }

			void onQuit() override;

		private:
			Surface _surface;
			RenderPass _pass;
			CmdPool _cmd_pool;
			SwapChain _swapchain;
			Semaphore _semaphore;
			std::array<CmdBuffer, MAX_FRAMES_IN_FLIGHT> _cmd_buffers;
			VkClearValue _clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

			WindowComponent* _window = nullptr;

			uint32_t _active_image_index = 0;
			uint32_t _image_index = 0;

			bool _framebufferResized = false;
			bool _is_init = false;
	};
}

#endif // __AK_RENDERER_COMPONENT__
