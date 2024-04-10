// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#ifndef __AK_WEBGPU_RENDERER__
#define __AK_WEBGPU_RENDERER__

#include <Drivers/WebGPU/PreCompiled.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Drivers/WebGPU/WebGPUInstance.h>
#include <Drivers/WebGPU/WebGPUDevice.h>

namespace Ak
{
	class AK_WEBGPU_API WebGPURenderer : public RHIRenderer
	{
		public:
			WebGPURenderer();

			inline WebGPUDevice& GetDevice() override;
			inline static WebGPUInstance& GetInstance();

			~WebGPURenderer() override;

		private:
			static UniquePtr<WebGPUInstance> p_instance;
			UniquePtr<WebGPUDevice> p_device;
	};

	inline bool IsWebGPUSupported() noexcept { return true; }
}

#include <Drivers/WebGPU/WebGPURenderer.inl>

#endif
