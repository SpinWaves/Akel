// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 20/02/2024

#ifndef __AK_RHI_DEVICE__
#define __AK_RHI_DEVICE__

#include <Graphics/PreCompiled.h>
#include <Utils/NonOwningPtr.h>
#include <Graphics/RHI/Enums.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIDevice
	{
		public:
			RHIDevice() = default;

			virtual NonOwningPtr<class RHIBuffer> CreateBuffer(BufferDescription description) = 0;
			virtual NonOwningPtr<class RHITexture> CreateTexture(TextureDescription description) = 0;
			virtual NonOwningPtr<class RHICmdManager> GetCmdManager() const noexcept = 0;
			virtual NonOwningPtr<class RHIRenderSurface> CreateRenderSurface() noexcept = 0;

			virtual void WaitForIdle() = 0;

			virtual ~RHIDevice() = default;
	};
}

#endif
