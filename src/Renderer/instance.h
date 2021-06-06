// This file is a part of AtlasEngine
// CREATED : 10/04/2021
// UPDATED : 06/06/2021

#ifndef __AE_INSTANCE__
#define __AE_INSTANCE__

#include <AEpch.h>
#include <Renderer/commandBuffer.h>
#include <Renderer/validationLayers.h>

namespace AE
{
    #define VK_FORMAT_RGBA_8_SRGB VK_FORMAT_B8G8R8A8_SRGB
    const int MAX_FRAMES_IN_FLIGHT = 2;

    class Instance : private CommandBuffer, private ValidationLayers
    {
        public:
			Instance();

            void init(SDL_Window* win, const char* vertexShader, const char* fragmentShader);
            void render();

            ~Instance();

        protected:
            void cleanup();

        private:
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}

#endif // __AE_INSTANCE__
