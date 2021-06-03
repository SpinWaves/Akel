// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_CONTEXT__
#define __AE_CONTEXT__

#include <AEpch.h>
#include <Core/core.h>

namespace AE
{    
    class Context
    {
        public:
            Context();

            void init(SDL_Window* window);
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

#endif // __AE_CONTEXT__
