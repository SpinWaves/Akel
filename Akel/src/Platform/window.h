// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 22/09/2021

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Akpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>
#include <Platform/messageBox.h>
#include <Platform/input.h>

enum windowSetting
{
    title,
    dimensions,
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

#define AK_WINDOW_MAX_SIZE 0xFFFF
#define AK_WINDOW_POS_CENTER 0xFFFE

namespace Ak
{
    class WindowComponent : public Instance, public Component
    {
        public:
            WindowComponent();

			void onAttach() override;
			void update() override;
			void onEvent(Input& input) override;
			void onQuit() override;

			// ================ Setters ================ //
			template <windowSetting T>
			void setSetting(const char* value)
			{
				switch(T)
				{
					case title: setTitle(value); break;
					case icon: setIcon(value); break;

					default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
				}
			}
			template <windowSetting T>
			void setSetting(bool value)
			{
				SDL_bool pass = value ? SDL_TRUE : SDL_FALSE;

				switch(T)
				{
					case fullscreen: setFullscreen(pass); break;
					case border:     setBordered(pass); break;
					case resizable:  setResizable(pass); break;
					case visible: setShow(pass); break;
					case vsync: Instance::setVsync(value); break;
					case maximize: setMaximize(pass); break;

					default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
				}
			}
			template <windowSetting T>
			void setSetting(float value)
			{
				switch(T)
				{
					case brightness: setBrightness(value); break;
					case opacity: setOpacity(value); break;

					default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
				}
			}
			template <windowSetting T>
			void setSetting(uint16_t x, uint16_t y)
			{
				switch(T)
				{
					case position:    _position.SET(x, y); setPos(x, y);  break;
					case dimensions:  _size.SET(x, y); setSize(x, y); break;
					case maximumSize: setMaxSize(x, y); break;
					case minimumSize: setMinSize(x, y); break;

					default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
				}
			}

            // Getters
            std::string getTitle();
            Maths::Vec2<uint16_t> getPosition();
            Maths::Vec2<uint16_t> getSize();
			SDL_Window* getNativeWindow()
			{
				return _window;
			}

            virtual ~WindowComponent();

		protected:
			void create();
            SDL_Window* _window = nullptr;

        private:

            std::string _title = "";
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

            uint32_t _flags = 0;

            SDL_Surface* _icon = nullptr;

			// Functions for window settings that use SDL2 functions. They are here to avoid you to link SDL2
			void setMaxSize(int x, int y);
			void setMinSize(int x, int y);
			void setPos(int x, int y);
			void setSize(int x, int y);
			void setFullscreen(SDL_bool value);
			void setBordered(SDL_bool value);
			void setResizable(SDL_bool value);
			void setShow(SDL_bool value);
			void setMaximize(SDL_bool value);
			void setBrightness(float value);
			void setOpacity(float value);
			void setTitle(const char* value);
			void setIcon(const char* value);
    };
}

#endif // __AK_WINDOW__
