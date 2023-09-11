// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 11/09/2023

#ifndef __AK_INPUT__
#define __AK_INPUT__

#include <Akpch.h>
#include <Core/profile.h>
#include <Platform/inputScanCode.h>

namespace Ak
{
    enum class action : uint8_t { up = (1 << 1), down = (1 << 2) };

    class AK_API Input
    {
		friend class Application;

        public:
            inline bool getInKey(const SDL_Scancode key, action type = action::down) const noexcept { return _keys[key] & static_cast<uint8_t>(type); }

            inline bool getInMouse(const uint8_t button, action type = action::down) const noexcept { return _mouse[button] & static_cast<uint8_t>(type); }
            inline bool isMouseMoving() const noexcept { return _xRel || _yRel; }

            inline int getX() const noexcept { return _x; }
            inline int getY() const noexcept { return _y; }

            inline int getXGlobal() const noexcept { return _gx; }
            inline int getYGlobal() const noexcept { return _gy; }

            inline int getXRel() const noexcept { return _xRel; }
            inline int getYRel() const noexcept { return _yRel; }

            inline bool isEnded() const noexcept { return _end; }
            inline constexpr void finish() noexcept { _end = true; }
            inline constexpr void run() noexcept { _end = false; }

            inline SDL_Event* getNativeEvent() noexcept { return &_event; }

            inline static void add_window(class WindowComponent* window) { _windows.push_back(window); }

        private:
            Input();
            void update();
            void reset() noexcept;
            ~Input() = default;

		private:
            inline static std::vector<class WindowComponent*> _windows;

            SDL_Event _event;
            std::array<uint8_t, SDL_NUM_SCANCODES> _keys;
            std::array<uint8_t, 5> _mouse;

			int _gx = 0;
			int _gy = 0;
            int _x = 0;
            int _y = 0;
            int _xRel = 0;
            int _yRel = 0;

            uint32_t _current_window = 0;

            bool _end = false;        
    };
}

#endif // __AK_INPUT__
