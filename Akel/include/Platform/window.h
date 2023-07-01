// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 01/07/2023

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Core/Components/baseComponent.h>
#include <Platform/messageBox.h>
#include <Maths/maths.h>
#include <Utils/utils.h>
#include <Core/profile.h>

#define AK_WINDOW_MAX_SIZE 0xFFFF
#define AK_WINDOW_MIN_SIZE 0
#define AK_WINDOW_POS_CENTER 0x2FFF0000u

namespace Ak
{
    class AK_API WindowComponent : public Component
    {
        friend class Input;
		friend class RendererComponent;

        public:
            WindowComponent();

			void onAttach() override;
            void update() override;
			void onQuit() override;
            void fetchSettings();

            inline SDL_Window* getNativeWindow() const noexcept { return _window; }

            std::string title = "Akel Window";
            std::string icon = "default_Akel_icon";
            
            Vec2i size;
            Vec2i pos;
            Vec2i minSize;
            Vec2i maxSize;
            
            float brightness = 1.0f;
            float opacity = 1.0f;

            bool fullscreen = false;
            bool border = true;
            bool resizable = true;
            bool visible = true;
            bool vsync = false;
            bool maximize = false;
            bool minimize = false;
			
            virtual ~WindowComponent() = default;

        protected:
            void create();
		
		protected:
            SDL_Window* _window = nullptr;

        private:
			void deserialize();
			void serialize();

		private:
            SDL_Surface* _icon = nullptr;
			int32_t _renderer = -1;
            uint32_t _flags = 0;
            uint32_t _window_id = 0;
			bool _window_has_focus = false;
    };
}

#endif // __AK_WINDOW__
