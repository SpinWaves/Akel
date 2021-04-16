// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 16/04/2021

#ifndef __WINDOW__
#define __WINDOW__

#include <AEpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>

enum windowType
{
    AE_WINDOW_OPENGL,
    AE_WINDOW_VULKAN,
    AE_WINDOW_POP_UP,
    AE_WINDOW_AUTO_TYPE
};

namespace AE
{
    class Window : public Context, public Instance
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, windowType type = AE_WINDOW_AUTO_TYPE);

            // Setters
            void setTitle(std::string title);
            void setFlags(uint32_t flags);
            void setPosition(uint16_t x, uint16_t y);
            void setSize(uint16_t width, uint16_t height);
            void setIcon(SDL_Surface* image);
            void setIcon(std::string imagePath);
            
            // Getters
            std::string getTitle();
            uint32_t getFlags();
            uint16_t getPositionX();
            uint16_t getPositionY();
            uint16_t getSizeW();
            uint16_t getSizeH();

            void initWindowRenderer();
            void update();

            void destroy();

            virtual ~Window();
        
        private:
            SDL_Window* _window;

            std::string _title;
            
            uint16_t _width;
            uint16_t _height;
            uint16_t _posx;
            uint16_t _posy;

            uint32_t _flags;

            SDL_Surface* _icon;
    };
}

#endif // __WINDOW__
