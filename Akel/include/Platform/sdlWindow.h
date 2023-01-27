// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/01/2023
// Updated : 27/01/2023

#ifndef __AK_SDL_WINDOW__
#define __AK_SDL_WINDOW__

#include <Akpch.h>

namespace Ak::sdl
{
	class Window
	{
		public:
			Window(std::string title, int x, int y, int w, int h, uint32_t flags);

			~Window() noexcept;

		private:
			SDL_Window* _window = nullptr;
	};
}

#endif
