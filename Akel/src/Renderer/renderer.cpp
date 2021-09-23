// This file is a part of Akel
// CREATED : 23/09/2021
// UPDATED : 23/09/2021

#include <Renderer/renderer.h>

namespace
{
    RendererComponent::RendererComponent() : Component("__renderer") {}
    RendererComponent::RendererComponent(WindowComponent& window) : Component("__renderer")
    {
        _window = window.getNativeWindow();
    }

    void RendererComponent::onAttach()
    {
        if(!_window)
            Core::log::report(FATAL_ERROR, "RendererComponent : no window passed to the renderer, \n call \"render_to_window()\" or create the RendererComponent with a window in arg");
        _instance = make_unique_ptr_w<Instance>(custom_malloc<Instance>());
        _instance.init(_window, _vertexShader.c_str(), _fragmentShader.c_str());
    }

    void RendererComponent::update()
    {
        _instance.render();
    }

    void RendererComponent::onEvent(Input& input) {}

    void RendererComponent::onQuit()
    {
        _instance.cleanup();
        _instance.reset(nullptr); // freeing _instance pointer
    }

    void RendererComponent::setShader(std::string vertexShader, std::string fragmentShader)
    {
        _vertexShader = std::move(vertexShader);
        _fragmentShader = std::move(fragmentShader);
    }

    void RendererComponent::render_to_window(WindowComponent& window)
    {
        _window = window.getNativeWindow();
    }
}
