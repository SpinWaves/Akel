// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 05/06/2021

#ifndef __AE_WINDOW__
#define __AE_WINDOW__

#include <AEpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>

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
    icon
};

enum windowComponents
{
	INPUTS
};

namespace AE
{
    class Window : public Instance, public Input
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

            void initWindowRenderer(const char* vert, const char* frag);

            // Setters            
            void setSetting(windowSetting setting, AE_text value);
            void setSetting(windowSetting setting, bool value);
            void setSetting(windowSetting setting, float value);
            void setSetting(windowSetting setting, uint16_t x, uint16_t y);

			void activateComponent(windowComponents component, bool activate);

            // Getters
            std::string getTitle();
            uint32_t getFlags();
            Maths::Vec2<uint16_t> getPosition();
            Maths::Vec2<uint16_t> getSize();

            void update();

            void destroy();

            virtual ~Window();
        
        private:
            SDL_Window* _window;

            std::string _title;
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

			std::unordered_map<windowComponents, bool> _components
			{
				{INPUTS, true},		// Inputs are activated by default
			};

            uint32_t _flags;

            SDL_Surface* _icon;
    };
}

#endif // __AE_WINDOW__
