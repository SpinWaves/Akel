// This file is a part of Akel
// CREATED : 10/04/2021
// UPDATED : 29/06/2021

#ifndef __AK_INSTANCE__
#define __AK_INSTANCE__

#include <Akpch.h>
#include <Renderer/commandBuffer.h>
#include <Renderer/validationLayers.h>

namespace Ak
{
    class Instance : private CommandBuffer, private ValidationLayers
    {
        public:
			Instance();

            void init(SDL_Window* win, const char* vertexShader, const char* fragmentShader);
            void render();

            ~Instance();

        protected:
            void cleanup();
			void setVsync(bool setter);
			bool getVsync();

        private:
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}

#endif // __AK_INSTANCE__
