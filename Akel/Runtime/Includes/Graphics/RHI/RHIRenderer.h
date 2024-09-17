// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_RHI_RENDERER__
#define __AK_RHI_RENDERER__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIRenderer
	{
		public:
			RHIRenderer() = default;

			virtual class RHIDevice& GetDevice() = 0;

			virtual ~RHIRenderer() = default;
	};
}

#endif 
