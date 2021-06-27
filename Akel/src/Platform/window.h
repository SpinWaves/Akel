// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 26/06/2021

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Akpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>
#include <Platform/messageBox.h>

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
	vsync
};

namespace Ak
{
    class Window : public Instance, public Component
    {
        public:
            Window(const char* componentName = "none");

            void create(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
			
			void onAttach() override;
			void update() override;		// overrides from Component class
			void onQuit() override;

			// ================ Setters ================ //
			template <windowSetting T>
			void setSetting(const char* value)
			{
				switch(T)
				{
					case title: setTitle(value); break;
					case icon: setIcon(value); break;

					default: std::cout << red << "Unable to modify window's parameter" << def << std::endl; break;
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

					default: std::cout << red << "Unable to modify window's parameter" << def << std::endl; break;
				}
			}
			template <windowSetting T>
			void setSetting(float value)
			{
				switch(T)
				{
					case brightness: setBrightness(value); break;
					case opacity: setOpacity(value); break;

					default: std::cout << red << "Unable to modify window's parameter" << def << std::endl; break;
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

					default: std::cout << red << "Unable to modify window's parameter" << def << std::endl; break;
				}
			}

            // Getters
            std::string getTitle();
            //uint32_t getFlags();
            Maths::Vec2<uint16_t> getPosition();
            Maths::Vec2<uint16_t> getSize();

            void destroy();

            virtual ~Window();
        
        private:
            SDL_Window* _window;

            std::string _title = "";
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

            uint32_t _flags;

            SDL_Surface* _icon;

			// Functions for window settings that use SDL2 functions. They are here to avoid you to link SDL2
			void setMaxSize(int x, int y);
			void setMinSize(int x, int y);
			void setPos(int x, int y);
			void setSize(int x, int y);
			void setFullscreen(SDL_bool value);
			void setBordered(SDL_bool value);
			void setResizable(SDL_bool value);
			void setShow(SDL_bool value);
			void setBrightness(float value);
			void setOpacity(float value);
			void setTitle(const char* value);
			void setIcon(const char* value);
    };
}

#endif // __AK_WINDOW__
