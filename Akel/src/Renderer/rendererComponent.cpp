// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 07/12/2022

#include <Renderer/rendererComponent.h>
#include <Renderer/Buffers/vk_ubo.h>

namespace Ak
{
    RendererComponent::RendererComponent(WindowComponent* window) : Component("__renderer_component"), _window(window) {}

    void RendererComponent::onAttach()
    {
        Render_Core::get().setWindow(_window);
        Render_Core::get().init();

    }

    void RendererComponent::onQuit()
    {
        Render_Core::get().getSwapChain().destroyFB();
		Render_Core::get().destroyCommandBuffers();
        Render_Core::get().getSwapChain().destroy();
    }
}
