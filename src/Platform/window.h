// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 12/04/2021

#ifndef __WINDOW__
#define __WINDOW__

#include <AEpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>

#define AE_WINDOW_OPENGL             SDL_WINDOW_OPENGL
#define AE_WINDOW_FULLSCREEN         SDL_WINDOW_FULLSCREEN
#define AE_WINDOW_VULKAN             SDL_WINDOW_VULKAN
#define AE_WINDOW_SHOWN              SDL_WINDOW_SHOWN
#define AE_WINDOW_HIDDEN             SDL_WINDOW_HIDDEN
#define AE_WINDOW_BORDERLESS         SDL_WINDOW_BORDERLESS
#define AE_WINDOW_RESIZABLE          SDL_WINDOW_RESIZABLE
#define AE_WINDOW_MNIMIZED           SDL_WINDOW_MINIMIZED
#define AE_WINDOW_MAXIMIZED          SDL_WINDOW_MAXIMIZED
#define AE_WINDOW_INPUT_GRABBED      SDL_WINDOW_INPUT_GRABBED
#define AE_WINDOW_INPUT_FOCUS        SDL_WINDOW_INPUT_FOCUS
#define AE_WINDOW_MOUSE_FOCUS        SDL_WINDOW_MOUSE_FOCUS
#define AE_WINDOW_FOREIGN            SDL_WINDOW_FOREIGN
#define AE_WINDOW_ALLOW_HIGHDPI      SDL_WINDOW_ALLOW_HIGHDPI
#define AE_WINDOW_MOUSE_CAPTURE      SDL_WINDOW_MOUSE_CAPTURE
#define AE_WINDOW_ALWAYS_ON_TOP      SDL_WINDOW_ALWAYS_ON_TOP
#define AE_WINDOW_SKIP_TASKBAR       SDL_WINDOW_SKIP_TASKBAR
#define AE_WINDOW_UTILITY            SDL_WINDOW_UTILITY
#define AE_WINDOW_TOOLTIP            SDL_WINDOW_TOOLTIP
#define AE_WINDOW_POPUP_MENU         SDL_WINDOW_POPUP_MENU

namespace AE
{
    class Window : public Context, public Instance
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t flags);

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
