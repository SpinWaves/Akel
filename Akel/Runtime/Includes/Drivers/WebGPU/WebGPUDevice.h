// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_WEBGPU_DEVICE__
#define __AK_WEBGPU_DEVICE__

#include <Drivers/WebGPU/PreCompiled.h>
#include <Graphics/RHI/RHIDevice.h>

namespace Ak
{
	class AK_WEBGPU_API WebGPUDevice : public RHIDevice
	{
		public:
			WebGPUDevice();

			NonOwningPtr<class RHIBuffer> CreateBuffer(BufferDescription description) override;
			NonOwningPtr<class RHITexture> CreateTexture(TextureDescription description) override;
			NonOwningPtr<class RHIRenderSurface> CreateRenderSurface() noexcept override;
			NonOwningPtr<class RHIGraphicPipeline> CreateGraphicPipeline() noexcept override;

			void WaitForIdle() override;

			~WebGPUDevice() override;

		private:
			void SelectAdapter() noexcept;

		private:
			WGPUDevice m_device = nullptr;
			WGPUAdapter m_adapter = nullptr;
	};
}

#endif

