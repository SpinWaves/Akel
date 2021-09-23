// This file is a part of Akel
// CREATED : 23/09/2021
// UPDATED : 23/09/2021

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent() : Component("__renderer"), _instance() {}
    RendererComponent::RendererComponent(SDL_Window* window) : Component("__renderer"), _instance()
    {
        _window = window;
    }

    void RendererComponent::onAttach()
    {
        if(!_window)
            Core::log::report(FATAL_ERROR, "RendererComponent : no window passed to the renderer, \n call \"render_to_window()\" or create the RendererComponent with a window in arg");
        _instance.init(_window, _vertexShader.c_str(), _fragmentShader.c_str());
    }

    void RendererComponent::update()
    {
        _instance.render();
    }

    void RendererComponent::onQuit()
    {
        _instance.cleanup();
    }

    void RendererComponent::setShader(std::string vertexShader, std::string fragmentShader)
    {
        _vertexShader = std::move(vertexShader);
        _fragmentShader = std::move(fragmentShader);
    }

    void RendererComponent::render_to_window(SDL_Window* window)
    {
        _window = window;
    }
}
