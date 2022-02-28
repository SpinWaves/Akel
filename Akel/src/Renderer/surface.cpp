// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 28/02/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    void RendererComponent::createSurface()
    {
        if(SDL_Vulkan_CreateSurface(window, instance, &surface) != SDL_TRUE)
            std::cout << SDL_GetError() << std::endl;
    }

    VkSurfaceFormatKHR RendererComponent::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for(const auto& availableFormat : availableFormats)
        {
            if(availableFormat.format == VK_FORMAT_R8G8B8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        }

        return availableFormats[0];
    }
}
