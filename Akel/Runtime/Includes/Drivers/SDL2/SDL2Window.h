// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_SDL2_WINDOW_H
#define AK_SDL2_WINDOW_H

#include <Drivers/SDL2/PreCompiled.h>
#include <Platform/SI/Window.h>

namespace Ak
{
	class AK_SDL2_API SDL2Window : public SIWindow
	{
		public:
			SDL2Window(std::size_t width, std::size_t height, const std::string& title, WindowStyle style);

			void CreateWindow() override;
			void UpdateWindowInfos() noexcept override;

			void SetPosition(const Vec2i& position) noexcept override;
			void SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept override;

			void SetSize(const Vec2i& size) noexcept override;
			void SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetMaxSize(const Vec2i& size) noexcept override;
			void SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetMinSize(const Vec2i& size) noexcept override;
			void SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetTitle(const std::string& title) override;

			~SDL2Window();

		private:
			SDL_Window* m_window = nullptr;
	};

}

#endif
