// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 09/03/2022

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Akpch.h>
#include <Core/core.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>
#include <Platform/messageBox.h>
#include <Platform/input.h>

#define AK_WINDOW_MAX_SIZE 0xFFFF
#define AK_WINDOW_POS_CENTER 0xFFFE

namespace Ak
{
    class WindowComponent : public Component
    {
        public:
            WindowComponent();

			void onAttach() override;
			void onEvent(Input& input) override;
            void update() override;
			void onQuit() override;

            union
            {
                std::string title = "Akel Window";
                std::string icon = Core::getAssetsDirPath() + "logo.png";
                
                Maths::Vec2<uint16_t> size(1280, 750);
                Maths::Vec2<uint16_t> pos(AK_WINDOW_POS_CENTER, AK_WINDOW_POS_CENTER);
                Maths::Vec2<uint16_t> minSize(0, 0);
                Maths::Vec2<uint16_t> maxSize(AK_WINDOW_MAX_SIZE, AK_WINDOW_MAX_SIZE);
                
                float brightness;
                float opacity;

                bool fullscreen;
                bool border;
                bool resizable;
                bool visible;
                bool vsync;
                bool maximize;
            };

            inline SDL_Window* getNativeWindow() noexcept { return _window; }
			
            ~WindowComponent() override;

		protected:
			void create();
            SDL_Window* _window = nullptr;

        private:
            uint32_t _flags = 0;
            SDL_Surface* _icon = nullptr;
    };
}

#endif // __AK_WINDOW__
