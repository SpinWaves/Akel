// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_GRAPHICS_ENUMS__
#define __AK_GRAPHICS_ENUMS__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	enum class RendererDrivers
	{
		Vulkan = 0,
		WebGPU,
		Auto,
		None,

		EndEnum
	};
	constexpr std::size_t RendererDriversCount = static_cast<std::size_t>(RendererDrivers::EndEnum);
}

#endif
