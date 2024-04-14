// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/04/2024
// Updated : 14/04/2024

#ifndef __AK_PLATFORM_SI_WINDOW_BACKEND__
#define __AK_PLATFORM_SI_WINDOW_BACKEND__

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
