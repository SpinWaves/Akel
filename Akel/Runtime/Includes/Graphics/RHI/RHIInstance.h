// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_INSTANCE_H
#define AK_RHI_INSTANCE_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIInstance
	{
		public:
			RHIInstance() = default;

			virtual SharedPtr<class RHIAdapter> PickAdapter(AdapterMinimalSpecs specs) = 0;
			virtual SharedPtr<class RHISurface> CreateSurface(class WindowComponent& window) noexcept = 0;

			virtual ~RHIInstance() = default;
	};
}

#endif
