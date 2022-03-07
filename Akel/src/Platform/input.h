// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 07/03/2022

#ifndef __AK_INPUT__
#define __AK_INPUT__

#include <Akpch.h>
#include <Platform/inputScanCode.h>

namespace Ak
{
    enum class action { up, down };

    class Input
    {
        public:
            Input();

            void update();
            inline void reset() noexcept
            {
                _xRel = 0;
                _yRel = 0;
                for(int i = 0; i < SDL_NUM_SCANCODES; i++)
                {
                    _keys[i].second = false;
                    if(i < _mouse.size())
                        _mouse[i].second = false;
                }
            }

            inline bool getInKey(const SDL_Scancode key, action type = action::down) const noexcept { return type == action::down ? _keys[key].first : _keys[key].second; }

            inline bool getInMouse(const uint8_t button, action type = action::down) const noexcept { return type == action::down ? _mouse[button].first : _mouse[button].second; }
            inline bool isMouseMoving() const noexcept { return _xRel || _yRel ? true : false; }

            inline int getX() const noexcept { return _x; }
            inline int getY() const noexcept { return _y; }

            inline int getXRel() const noexcept { return _xRel; }
            inline int getYRel() const noexcept { return _yRel; }

            inline bool isEnded() const noexcept { return _end; }
            inline constexpr void finish() noexcept { _end = true; }

            inline SDL_Event* getNativeEvent() noexcept { return &_event; }

            ~Input() = default;

        private:
            SDL_Event _event;
            std::array<std::pair<bool, bool>, SDL_NUM_SCANCODES> _keys;
            std::array<std::pair<bool, bool>, 5> _mouse;

            int _x = 0;
            int _y = 0;
            int _xRel = 0;
            int _yRel = 0;

            bool _end = false;
    };
}

#endif // __AK_INPUT__
