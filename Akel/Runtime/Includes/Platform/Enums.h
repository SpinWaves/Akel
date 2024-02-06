// This file is a part of Akel
// Authors : @maldavid
// Created : 06/02/2024
// Updated : 06/02/2024

#ifndef __AK_PLATFORM_ENUMS__
#define __AK_PLATFORM_ENUMS__

#include <Platform/PreCompiled.h>

namespace Ak
{
	enum class WindowStyle
	{
		TitleBar = 0,
		Borders,
		NoDecorations, // No title bar, no borders
		Fullscreen, // Fullscreen at creation
		Closable,
		Resizable,

		EndEnum
	};
	constexpr std::size_t WindowStyleCount = static_cast<std::size_t>(WindowStyle::EndEnum);
}

#endif
