// This file is a part of Akel
// Authors : @maldavid
// Created : 06/02/2024
// Updated : 08/02/2024

#ifndef __AK_PLATFORM_ENUMS__
#define __AK_PLATFORM_ENUMS__

#include <Platform/PreCompiled.h>

namespace Ak
{
	namespace WindowStyle // not enum class to allow binary operations like Ak::WindowStyle::NoBorders | Ak::WindowStyle::Closable
	{
		enum : std::uint32_t
		{
			NoBorders = 0,
			Fullscreen = 1 << 0, // Fullscreen at creation
			FullscreenDesktop = 1 << 1, // Fullscreen at desktop resolution at creation
			Closable = 1 << 2,
			Resizable = 1 << 3,
		};
	}
	constexpr std::size_t WindowStyleCount = 5;
}

#endif
