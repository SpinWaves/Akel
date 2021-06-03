// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 03/06/2021

#ifndef __AE_WINDOW__
#define __AE_WINDOW__

#include <AEpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>

enum windowType
{
    AE_WINDOW_OPENGL,
    AE_WINDOW_VULKAN,
    AE_WINDOW_POP_UP,
    AE_WINDOW_AUTO_TYPE
};

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
    class Window : public Context, public Instance, public Input
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, windowType type = AE_WINDOW_AUTO_TYPE);

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

            static uint16_t getNumberOfWindows();
            static bool isWindowOpenGL(uint16_t windowNumber);
        
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

            inline static std::map<uint16_t, bool> _winInfoSystem;
            
			void initWindowRenderer();
    };
}

#endif // __AE_WINDOW__
