// This file is a part of Akel
// Author : @kbz_8
// CREATED : 23/09/2021
// Updated : 02/03/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent() : Component("__renderer_component") {}
    RendererComponent::RendererComponent(SDL_Window* win) : Component("__renderer_component"), window(win) {}

    void RendererComponent::onAttach()
    {
        if(!window)
            Core::log::report(FATAL_ERROR, "RendererComponent : no window passed to the renderer, \n call \"render_to_window()\" or create the RendererComponent with a window in arg");

        vertices =
        {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
        };

        indices = {0, 1, 2, 2, 3, 0};

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createVertexBuffer();
        createIndexBuffer();
        createCommandBuffers();
        createSemaphores();

        _instanceInitialized = true;
    }

    void RendererComponent::onRender()
    {
        if(!_instanceInitialized)
            Core::log::report(FATAL_ERROR, "Vulkan : unable to render, you need to init the instance before");

        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult res = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if(res != VK_SUCCESS && res != VK_TIMEOUT && res != VK_NOT_READY && res != VK_SUBOPTIMAL_KHR)
        {
            switch(res)
            {
                case VK_ERROR_OUT_OF_HOST_MEMORY : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_OUT_OF_HOST_MEMORY)"); break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_OUT_OF_DEVICE_MEMORY)"); break;
                case VK_ERROR_DEVICE_LOST : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_DEVICE_LOST)"); break;
                case VK_ERROR_OUT_OF_DATE_KHR : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_OUT_OF_DATE_KHR)"); break;
                case VK_ERROR_SURFACE_LOST_KHR : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_SURFACE_LOST_KHR)"); break;
                case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error (VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)"); break;

                default : Core::log::report(FATAL_ERROR, "Vulkan : vkAquireNextImageKHR returned an error"); break;
            }
        }

        if(imagesInFlight[imageIndex] != VK_NULL_HANDLE)
            vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);

        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device, 1, &inFlightFences[currentFrame]);

        if(vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to submit draw command buffer");

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(presentQueue, &presentInfo);

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void RendererComponent::onQuit()
    {
        vkDeviceWaitIdle(device);

        for(auto framebuffer : swapChainFramebuffers)
            vkDestroyFramebuffer(device, framebuffer, nullptr);

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for(auto imageView : swapChainImageViews)
            vkDestroyImageView(device, imageView, nullptr);

        vkDestroySwapchainKHR(device, swapChain, nullptr);

        vkDestroyBuffer(device, indexBuffer, nullptr);
        vkFreeMemory(device, indexBufferMemory, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);

        for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);

        if(enableValidationLayers)
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }
}
