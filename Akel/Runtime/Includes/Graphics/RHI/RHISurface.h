// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_SURFACE_H
#define AK_RHI_SURFACE_H

#include <Graphics/PreCompiled.h>

namespace Ak
{
	class AK_GRAPHICS_API RHISurface
	{
		public:
			RHISurface(class WindowComponent& window) {}

			virtual ~RHISurface() = default;

		private:
	};
}

#endif
