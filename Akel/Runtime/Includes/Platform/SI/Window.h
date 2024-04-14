// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 14/04/2024

#ifndef __AK_PLATFORM_SI_WINDOW__
#define __AK_PLATFORM_SI_WINDOW__

#include <Platform/PreCompiled.h>
#include <Maths/Vec2.h>
#include <Platform/Enums.h>
#include <Platform/SI/WindowBackend.h>
#include <Utils/NonCopyable.h>

namespace Ak
{
	class AK_PLATFORM_API SIWindow : public NonCopyable
	{
		public:
			SIWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style);

			virtual void CreateWindow() = 0;
			virtual void UpdateWindowInfos() noexcept {}

			inline std::size_t GetWidth() const noexcept { return m_size.x; }
			inline std::size_t GetHeight() const noexcept { return m_size.y; }

			virtual void SetPosition(const Vec2i& position) noexcept {}
			virtual void SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept {}

			virtual void SetSize(const Vec2i& size) noexcept {}
			virtual void SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept {}

			virtual void SetMaxSize(const Vec2i& size) noexcept {}
			virtual void SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept {}

			virtual void SetMinSize(const Vec2i& size) noexcept {}
			virtual void SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept {}

			virtual void SetTitle(const std::string& title) {}

			inline const std::string& GetTitle() const { return m_title; }
			inline const Vec2i& GetPosition() const noexcept { return m_pos; }
			inline const Vec2i& GetSize() const noexcept { return m_size; }
			inline const Vec2i& GetMinSize() const noexcept { return m_min_size; }
			inline const Vec2i& GetMaxSize() const noexcept { return m_max_size; }
			inline WindowBackend GetWindowBackend() const noexcept { return m_backend; }

			AK_FORCEINLINE bool IsMaximized() const noexcept { return m_is_maximized; }
			AK_FORCEINLINE bool IsMinimized() const noexcept { return m_is_minimized; }
			AK_FORCEINLINE bool IsFullScreen() const noexcept { return m_is_fullscreen; }
			AK_FORCEINLINE bool IsFullScreenDesktop() const noexcept { return m_is_fullscreen_desktop; }
			AK_FORCEINLINE bool IsResizable() const noexcept { return m_is_resizable; }
			AK_FORCEINLINE bool HasBorders() const noexcept { return !(m_style & WindowNoBorders); }

			virtual ~SIWindow();

		protected:
			std::string m_title;
			WindowBackend m_backend;
			Vec2i m_pos;
			Vec2i m_size;
			Vec2i m_max_size;
			Vec2i m_min_size;
			WindowStyle m_style;
			bool m_is_maximized;
			bool m_is_minimized;
			bool m_is_fullscreen;
			bool m_is_fullscreen_desktop;
			bool m_is_resizable;
	};
}

#endif
