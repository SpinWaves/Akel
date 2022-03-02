// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 28/02/2022

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Akpch.h>
#include <Core/core.h>
#include <Renderer/rendererComponent.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>
#include <Platform/messageBox.h>
#include <Platform/input.h>


#define AK_WINDOW_MAX_SIZE 0xFFFF
#define AK_WINDOW_POS_CENTER 0xFFFE

namespace Ak
{
    enum class winsets
    {
        title,
        size,
        position,
        fullscreen,
        border,
        brightness,
        opacity,
        resizable,
        visible,
        maximumSize,
        minimumSize,
        icon,
        vsync,
        maximize
    };

    class WindowComponent : public Component
    {
        public:
            WindowComponent();

			void onAttach() override;
			void onEvent(Input& input) override;
			void onQuit() override;

			void setSetting(winsets setting, const char* value);
			void setSetting(winsets setting, bool value);
			void setSetting(winsets setting, float value);
			void setSetting(winsets setting, uint16_t x, uint16_t y);

            // Getters
            inline const std::string& getTitle() const noexcept { return _title; }
            inline const Maths::Vec2<uint16_t>& getPosition() const noexcept { return _position; }
            const Maths::Vec2<uint16_t>& getSize();
			inline SDL_Window* getNativeWindow() const noexcept { return _window; }

            ~WindowComponent() override;

		protected:
			void create();
            SDL_Window* _window = nullptr;

        private:

            std::string _title = "";
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

            uint32_t _flags = 0;

            SDL_Surface* _icon = nullptr;
    };
}

#endif // __AK_WINDOW__
