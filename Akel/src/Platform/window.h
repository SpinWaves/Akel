// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 03/04/2022

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
#define AK_WINDOW_MIN_SIZE 0
#define AK_WINDOW_POS_CENTER 0x2FFF0000u

namespace Ak
{
    class WindowComponent : public Component
    {
        friend class Input;
        
        public:
            WindowComponent();

			void onAttach() override;
			void onEvent(Input& input) override;
            void update() override;
			void onQuit() override;
            void fetchSettings();

            inline SDL_Window* getNativeWindow() const noexcept { return _window; }

            std::string title = "Akel Window";
            std::string icon = Core::getAssetsDirPath() + "logo.png";
            
            Maths::Vec2<int> size;
            Maths::Vec2<int> pos;
            Maths::Vec2<int> minSize;
            Maths::Vec2<int> maxSize;
            
            float brightness = 1.0f;
            float opacity = 1.0f;

            bool fullscreen = false;
            bool border = true;
            bool resizable = true;
            bool visible = true;
            bool vsync = true;
            bool maximize = false;
            bool minimize = false;
			
            virtual ~WindowComponent() = default;

        protected:
            void create();
            SDL_Window* _window = nullptr;

        private:
            uint32_t _flags = 0;
            SDL_Surface* _icon = nullptr;
            uint32_t _window_id = 0;
    };
}

#endif // __AK_WINDOW__
