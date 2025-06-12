// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_PLATFORM_SI_WINDOW_BACKEND_H
#define AK_PLATFORM_SI_WINDOW_BACKEND_H

#include <Platform/Enums.h>

namespace Ak
{
	struct WindowBackend
	{
		union
		{
			struct
			{
				void* display;
				unsigned long window;
			} x11;
			struct
			{
				void* display;
				void* surface;
				void* shell_surface;
			} wayland;
			struct
			{
				void* window;
			} win_api;
			struct
			{
				void* window;
			} cocoa;
		};

		WindowBackendType backend_in_use;
	};
}

#endif
