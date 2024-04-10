// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2024
// Updated : 10/04/2024

#ifndef __AK_GRAPHICS_ENUMS__
#define __AK_GRAPHICS_ENUMS__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	enum class RendererDrivers
	{
		Vulkan = 0,
		None = 1,

		EndEnum
	};
	constexpr std::size_t RendererDriversCount = static_cast<std::size_t>(RendererDrivers::EndEnum);
}

#endif
