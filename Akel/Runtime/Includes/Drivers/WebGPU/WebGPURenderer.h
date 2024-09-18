// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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

			std::uint32_t LoadNewDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept override;
			inline WebGPUDevice& GetDevice(std::uint32_t index) override;
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
