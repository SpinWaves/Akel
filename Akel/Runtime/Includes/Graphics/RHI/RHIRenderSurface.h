// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_RENDER_SURFACE_H
#define AK_RHI_RENDER_SURFACE_H

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
