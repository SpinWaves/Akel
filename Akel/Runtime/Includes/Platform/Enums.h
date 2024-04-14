// This file is a part of Akel
// Authors : @maldavid
// Created : 06/02/2024
// Updated : 14/04/2024

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
		WindowDummy = 1 << 5, // For internal use
	};
	using WindowStyle = int;
	constexpr std::size_t WindowStyleCount = 7;

	enum class WindowBackendType
	{
		X11 = 0,
		Wayland,
		WinAPI,
		Cocoa,

		EndEnum
	};
	constexpr std::size_t WindowBackendTypeCount = static_cast<std::size_t>(WindowBackendType::EndEnum);
}

#endif
