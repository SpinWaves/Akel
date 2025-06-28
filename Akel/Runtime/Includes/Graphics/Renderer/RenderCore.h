// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RENDERER_CORE_H
#define AK_RENDERER_CORE_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/RHIAdapter.h>
#include <Graphics/RHI/RHIDevice.h>
#include <Graphics/RHI/RHIInstance.h>

namespace Ak
{
	class AK_GRAPHICS_API RenderCore
	{
		public:
			RenderCore(UniquePtr<RHIInstance> instance);

			inline RHIInstance& GetInstance() const noexcept { return *p_instance; }
			inline RHIDevice& GetDevice() const noexcept { return *p_device; }
			inline RHIAdapter& GetAdapter() const noexcept { return *p_adapter; }

			~RenderCore();

		private:
			static RenderCore* s_instance;

			UniquePtr<RHIInstance> p_instance = nullptr;
			SharedPtr<RHIAdapter> p_adapter = nullptr;
			SharedPtr<RHIDevice> p_device = nullptr;
	};
}

#endif
