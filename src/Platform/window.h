// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 18/04/2021

#ifndef __WINDOW__
#define __WINDOW__

#include <AEpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/messageBox.h>

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

namespace AE
{
    class Window : public Context, public Instance
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, windowType type = AE_WINDOW_AUTO_TYPE);

            // Setters            
            void setSetting(windowSetting setting, const char* value);
            void setSetting(windowSetting setting, bool value);
            void setSetting(windowSetting setting, float value);
            void setSetting(windowSetting setting, uint16_t x, uint16_t y);
            
            // Getters
            std::string getTitle();
            uint32_t getFlags();
            Maths::Vec2<uint16_t> getPosition();
            Maths::Vec2<uint16_t> getSize();

            void initWindowRenderer();
            void update();

            void destroy();

            virtual ~Window();
        
        private:
            SDL_Window* _window;

            std::string _title;
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

            uint32_t _flags;

            SDL_Surface* _icon;
    };
}

#endif // __WINDOW__
