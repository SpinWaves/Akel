// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_ADAPTER_H
#define AK_RHI_ADAPTER_H

#include <Graphics/PreCompiled.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIAdapter
	{
		public:
			RHIAdapter() = default;

			virtual SharedPtr<class RHIDevice> CreateDevice() = 0;

			virtual ~RHIAdapter() = default;

		private:
	};
}

#endif
