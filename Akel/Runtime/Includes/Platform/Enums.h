// This file is a part of Akel
// Authors : @maldavid
// Created : 06/02/2024
// Updated : 19/02/2024

#ifndef __AK_PLATFORM_ENUMS__
#define __AK_PLATFORM_ENUMS__

#include <Platform/PreCompiled.h>

namespace Ak
{
	enum WindowStyleBits
	{
		WindowDefault = 0,
		WindowNoBorders = 1 << 0,
		WindowFullscreen = 1 << 1, // Fullscreen at creation
		WindowFullscreenDesktop = 1 << 2, // Fullscreen at desktop resolution at creation
		WindowClosable = 1 << 3,
		WindowResizable = 1 << 4,
	};
	using WindowStyle = int;
	constexpr std::size_t WindowStyleCount = 6;
}

#endif
