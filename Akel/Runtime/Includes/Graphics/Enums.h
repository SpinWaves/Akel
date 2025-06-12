// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_GRAPHICS_ENUMS_H
#define AK_GRAPHICS_ENUMS_H

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
