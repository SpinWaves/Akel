// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_RENDERER_H
#define AK_RHI_RENDERER_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Defs.h>
#include <Utils/Result.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIRenderer
	{
		public:
			RHIRenderer() = default;

			virtual std::uint32_t LoadNewDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept = 0;
			virtual class RHIDevice& GetDevice(std::uint32_t index) = 0;

			virtual ~RHIRenderer() = default;
	};
}

#endif 
