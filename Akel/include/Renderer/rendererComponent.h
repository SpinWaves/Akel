// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 16/06/2023

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Core/profile.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include <Renderer/fps.h>
#include "Pipeline/vk_shader.h"
#include "Pipeline/vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>

#include <Renderer/Core/vk_fence.h>
#include <Renderer/Core/vk_surface.h>
#include <Renderer/Core/vk_semaphore.h>
#include <Renderer/Command/cmd_manager.h>
#include <Renderer/SwapChain/vk_swapchain.h>
#include <Renderer/RenderPass/vk_render_pass.h>

namespace Ak
{
	class AK_API RendererComponent final : public Component
	{
		public:
			RendererComponent(WindowComponent* window);

			void onAttach() override;
			void onQuit() override;

			bool beginFrame();
			void endFrame();

			inline WindowComponent* getWindow() noexcept { return _window; }
			inline void setWindow(WindowComponent* window) noexcept { _window = window; }

			inline Surface& getSurface() noexcept { return _surface; }
			inline CmdPool& getCmdPool() noexcept { return _cmd.getCmdPool(); }
			inline SwapChain& getSwapChain() noexcept { return _swapchain; }
			inline Semaphore& getSemaphore(int i) noexcept { return _semaphores[i]; }
			inline CmdBuffer& getCmdBuffer(int i) noexcept { return _cmd.getCmdBuffer(i); }
			inline CmdBuffer& getActiveCmdBuffer() noexcept { return _cmd.getCmdBuffer(_active_image_index); }
			inline uint32_t getActiveImageIndex() const noexcept { return _active_image_index; }
			inline uint32_t getSwapChainImageIndex() const noexcept { return _swapchain_image_index; }
			inline bool isInit() const noexcept { return _is_init; }

			inline constexpr void requireFrameBufferResize() noexcept { _framebufferResize = true; }
			inline bool isFrameBufferResizeRequested() const noexcept { return _framebufferResize; }

			inline void setMaxFPS(std::uint32_t max) noexcept { _fps.setMaxFPS(max); _max_fps = max; }
			inline uint32_t getFPS() const noexcept { return _fps.getFPS(); }
			inline bool isRendering() const noexcept { return _fps.makeRendering(); }

		private:
			CounterFPS _fps;
			CmdManager _cmd;
			Surface _surface;
			SwapChain _swapchain;
			std::array<Semaphore, MAX_FRAMES_IN_FLIGHT> _semaphores;
			std::mutex _mutex;

			WindowComponent* _window = nullptr;

			uint32_t _active_image_index = 0;
			uint32_t _swapchain_image_index = 0;

			uint32_t _max_fps = 100'000;

			bool _framebufferResize = false;
			bool _is_init = false;
			bool _rendering_began = false;
	};
}

#endif // __AK_RENDERER_COMPONENT__
