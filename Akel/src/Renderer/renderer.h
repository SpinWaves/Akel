// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 23/09/2021

#ifndef __AK_RENDERER__
#define __AK_RENDERER__

#define VK_FORMAT_RGBA_8_SRGB VK_FORMAT_B8G8R8A8_SRGB
const int MAX_FRAMES_IN_FLIGHT = 2;

#include <Renderer/instance.h>
#include <Renderer/pipeline.h>
#include <Renderer/swapChain.h>
#include <Renderer/queues.h>
#include <Renderer/surface.h>
#include <Renderer/renderPass.h>
#include <Renderer/lowestInheritance.h>
#include <Renderer/imageView.h>
#include <Renderer/frameBuffer.h>
#include <Renderer/rendering.h>
#include <Renderer/validationLayers.h>
#include <Renderer/vertexBuffer.h>

#include <Core/core.h>
#include <Platform/platform.h>

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
            explicit RendererComponent(WindowComponent& window);
            explicit RendererComponent();

            void onAttach() override;
            void update() override;
            void onEvent(Ak::Input& input) override;
            void onQuit() override;

            void setShader(std::string vertexShader, std::string fragmentShader);
            void render_to_window(WindowComponent& window);

            ~RendererComponent() = default;

        private:
            unique_ptr_w<Instance> _instance;
            std::string _vertexShader = Core::getMainDirPath() + "Ressources/Shaders/vert.spv";
            std::string _fragmentShader = Core::getMainDirPath() + "Ressources/Shader/frag.spv";
            SDL_Window* _window;
    };
}

#endif // __AK_RENDERER__
