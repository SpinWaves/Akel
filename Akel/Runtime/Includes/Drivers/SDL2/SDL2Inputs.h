// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2024
// Updated : 11/02/2024

#ifndef __AK_SDL2_INPUTS__
#define __AK_SDL2_INPUTS__

#include <Drivers/SDL2/PreCompiled.h>
#include <Platform/SI/Input.h>

namespace Ak
{
	class AK_SDL2_API SDL2Inputs : public Inputs
	{
		friend class PlatformModule;

		public:
			SDL2Inputs() = default;

			bool GetKeyPressed(const std::uint32_t button) const noexcept override;
			bool GetKeyReleased(const std::uint32_t button) const noexcept override;
			bool GetMouseButtonPressed(const std::uint8_t button) const noexcept override;
			bool GetMouseButtonReleased(const std::uint8_t button) const noexcept override;
			inline std::int32_t GetX() const noexcept override { return m_x; }
			inline std::int32_t GetY() const noexcept override { return m_y; }
			inline std::int32_t GetXGlobal() const noexcept override { return m_gx; }
			inline std::int32_t GetYGlobal() const noexcept override { return m_gy; }
			inline std::int32_t GetXRel() const noexcept override { return m_x_rel; }
			inline std::int32_t GetYRel() const noexcept override { return m_y_rel; }

			~SDL2Inputs() = default;

		private:
			void Update() override;

		private:
			SDL_Event m_event;
			std::array<std::uint8_t, SDL_NUM_SCANCODES> m_keys;
			std::array<std::uint8_t, 5> m_mouse;
			std::int32_t m_gx = 0;
			std::int32_t m_gy = 0;
			std::int32_t m_x = 0;
			std::int32_t m_y = 0;
			std::int32_t m_x_rel = 0;
			std::int32_t m_y_rel = 0;
	};
}

#endif
