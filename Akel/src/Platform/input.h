// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 01/10/2022

#ifndef __AK_INPUT__
#define __AK_INPUT__

#include <Akpch.h>
#include <Platform/inputScanCode.h>

namespace Ak
{
    enum class action : uint8_t { up = (1 << 1), down = (1 << 2) };

    class Input
    {
        public:
            Input();

            void update();
            inline void reset() noexcept
            {
                _xRel = 0;
                _yRel = 0;
            }

            inline bool getInKey(const SDL_Scancode key, action type = action::down) const noexcept { return _keys[key] & static_cast<uint8_t>(type); }

            inline bool getInMouse(const uint8_t button, action type = action::down) const noexcept { return _mouse[button] & static_cast<uint8_t>(type); }
            inline bool isMouseMoving() const noexcept { return _xRel || _yRel; }

            inline int getX() const noexcept { return _x; }
            inline int getY() const noexcept { return _y; }

            inline int getXRel() const noexcept { return _xRel; }
            inline int getYRel() const noexcept { return _yRel; }

            inline bool isEnded() const noexcept { return _end; }
            inline constexpr void finish() noexcept { _end = true; }
            inline constexpr void run() noexcept { _end = false; }

            inline SDL_Event* getNativeEvent() noexcept { return &_event; }

            inline static void add_window(class WindowComponent* window) { _windows.push_back(window); }

            ~Input() = default;

        private:
            SDL_Event _event;
            std::array<uint8_t, SDL_NUM_SCANCODES> _keys;
            std::array<uint8_t, 5> _mouse;

            int _x = 0;
            int _y = 0;
            int _xRel = 0;
            int _yRel = 0;

            bool _end = false;

            uint32_t _current_window = 0;
            
            inline static std::vector<class WindowComponent*> _windows;
    };
}

#endif // __AK_INPUT__
