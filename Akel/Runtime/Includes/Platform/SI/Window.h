// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 07/02/2024

#ifndef __AK_PLATFORM_SI_WINDOW__
#define __AK_PLATFORM_SI_WINDOW__

#include <Platform/PreCompiled.h>
#include <Maths/Vec2.h>
#include <Platform/Enums.h>
#include <Utils/NonCopyable.h>

namespace Ak
{
	class AK_PLATFORM_API SIWindow : public NonCopyable
	{
		public:
			SIWindow(std::size_t width, std::size_t height, WindowStyle style);
			SIWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style);

			inline std::size_t GetWidth() const noexcept { return m_size.x; }
			inline std::size_t GetHeight() const noexcept { return m_size.y; }

			void SetPosition(const Vec2i& position) noexcept;
			void SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept;

			void SetSize(const Vec2i& size) noexcept;
			void SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;

			void SetMaxSize(const Vec2i& size) noexcept;
			void SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;

			void SetMinSize(const Vec2i& size) noexcept;
			void SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;

			void SetTitle(const std::string& title);

			std::string GetTitle() const;
			inline const Vec2i& GetPosition() const noexcept { return m_pos; }
			inline const Vec2i& GetSize() const noexcept { return m_size; }
			inline const Vec2i& GetMinSize() const noexcept { return m_min_size; }
			inline const Vec2i& GetMaxSize() const noexcept { return m_max_size; }

			~SIWindow();

		private:
			WindowStyle m_style;
			Vec2i m_pos;
			Vec2i m_size;
			Vec2i m_max_size;
			Vec2i m_min_size;
	};
}

#endif
