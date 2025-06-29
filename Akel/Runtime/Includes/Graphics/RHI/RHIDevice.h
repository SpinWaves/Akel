// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_DEVICE_H
#define AK_RHI_DEVICE_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/RHIAdapter.h>
#include <Graphics/RHI/Enums.h>
#include <Graphics/RHI/Defs.h>
#include <Maths/Vec2.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIDevice
	{
		public:
			RHIDevice(class RHIInstance& instance, SharedPtr<RHIAdapter> adapter) : p_adapter(adapter) {}

			virtual SharedPtr<class RHIBuffer> CreateBuffer(BufferDescription description) = 0;
			virtual SharedPtr<class RHITexture> CreateTexture(TextureDescription description) = 0;
			virtual SharedPtr<class RHISwapchain> CreateSwapchain(SharedPtr<class RHISurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb) noexcept = 0;
			virtual SharedPtr<class RHIGraphicPipeline> CreateGraphicPipeline(GraphicPipelineDescription description) noexcept = 0;
			virtual SharedPtr<class RHICommandEncoder> CreateCommandBuffer() noexcept = 0;
			virtual SharedPtr<class RHICommandBuffer> CreateCommandBuffer(class RHICommandEncoder& encoder) noexcept = 0;

			virtual void WaitForIdle() = 0;

			inline SharedPtr<RHIAdapter> GetAdapter() const { return p_adapter; }

			virtual ~RHIDevice() = default;

		protected:
			SharedPtr<RHIAdapter> p_adapter;
	};
}

#endif
