// This file is a part of Akel
// CREATED : 10/04/2021
// UPDATED : 06/06/2021

#ifndef __AK_INSTANCE__
#define __AK_INSTANCE__

#include <Akpch.h>
#include <Renderer/commandBuffer.h>
#include <Renderer/validationLayers.h>

namespace Ak
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

#endif // __AK_INSTANCE__
