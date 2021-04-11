// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 05/04/2021

#ifndef __CONTEXT__
#define __CONTEXT__

#include <AEpch.h>
#include <Utils/utils.h>

namespace AE
{    
    class Context
    {
        public:
            Context();

            void init(SDL_Window* window);
            void SwapBuffers();
            void setVerticalSync(bool enabled);
            void clearRendering();
            bool isCreated();
            void destroy();

            virtual ~Context();
        
        private:
            SDL_Window* _window;
            SDL_GLContext _glcontext;
    };
}

#endif // __CONTEXT__