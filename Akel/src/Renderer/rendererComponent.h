// This file is a part of Akel
// CREATED : 23/09/2021
// UPDATED : 23/09/2021

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Renderer/instance.h>

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
            explicit RendererComponent(SDL_Window* window);
            explicit RendererComponent();

            void onAttach() override;
            void update() override;
            void onQuit() override;

            void setShader(std::string vertexShader, std::string fragmentShader);
            void render_to_window(SDL_Window* window);

            ~RendererComponent() = default;

        private:
            Instance _instance;
            std::string _vertexShader = Core::getMainDirPath() + "Ressources/shaders/vert.spv";
            std::string _fragmentShader = Core::getMainDirPath() + "Ressources/shaders/frag.spv";
            SDL_Window* _window;
    };
}

#endif // __AK_RENDERER_COMPONENT__
