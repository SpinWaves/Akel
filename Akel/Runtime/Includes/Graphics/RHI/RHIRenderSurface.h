// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/02/2024
// Updated : 23/02/2024

#ifndef __AK_RHI_RENDER_SURFACE__
#define __AK_RHI_RENDER_SURFACE__

#include <Utils/NonOwningPtr.h>
#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Enums.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIRenderSurface
	{
		public:
			RHIRenderSurface(NonOwningPtr<class RHIDevice> device) : c_device(device) {}

			virtual NonOwningPtr<class RHISwapChain> GetSwapChain() = 0;
			virtual NonOwningPtr<class RHISurface> GetSurface() = 0;
			virtual NonOwningPtr<class RHICmdManager> GetCmdManager() const noexcept = 0;
			virtual NonOwningPtr<class RHISyncManager> GetSyncManager() = 0;

			inline NonOwningPtr<class RHIDevice> GetDevice() const noexcept { return c_device; }

			virtual ~RHIRenderSurface() = default;

		private:
			const NonOwningPtr<class RHIDevice> c_device;
	};
}

#endif
