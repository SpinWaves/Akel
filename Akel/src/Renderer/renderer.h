// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 29/06/2021

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

#include <Core/Components/components.h>

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
            explicit RendererComponent();

            void onAttach() override;
            void update() override;
            void onEvent(Ak::Input& input) override;
            void onQuit() override;

            ~RendererComponent();

        private:
    };
}

#endif // __AK_RENDERER__
