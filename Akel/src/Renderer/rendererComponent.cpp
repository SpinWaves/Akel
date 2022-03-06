// This file is a part of Akel
// Author : @kbz_8
// CREATED : 23/09/2021
// Updated : 06/03/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent() : Component("__renderer_component") {}
    RendererComponent::RendererComponent(shader internal) : Component("__renderer_component")
    {
        useShader(internal);
    }
    RendererComponent::RendererComponent(WindowComponent* win, shader internal) : Component("__renderer_component"), window(win)
    {
        useShader(internal);
    }
    RendererComponent::RendererComponent(WindowComponent* win) : Component("__renderer_component"), window(win) {}

    void RendererComponent::onAttach()
    {
        if(!window)
            Core::log::report(FATAL_ERROR, "RendererComponent : no window passed to the renderer, \n call \"render_to_window()\" or create the RendererComponent with a window in arg");

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
        if(res == VK_ERROR_OUT_OF_DATE_KHR)
        {
            recreateSwapChain();
            return;
        }
        else if(res != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan rendering : failed to acquire swap chain image");


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
			Core::log::report(FATAL_ERROR, "Vulkan rendering : failed to submit draw command buffer");

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        res = vkQueuePresentKHR(presentQueue, &presentInfo);

        if(res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR || framebufferResized)
        {
            framebufferResized = false;
            recreateSwapChain();
        }
        else if(res != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan rendering : failed to present swap chain image");

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void RendererComponent::onQuit()
    {
        cleanupSwapChain();

        for(Entity2D& elem : entities2D)
        {
            if(elem.__data.indexData.size() != 0)
            {
                vkDestroyBuffer(device, elem.__data.indexBuffer, nullptr);
                vkFreeMemory(device, elem.__data.indexBufferMemory, nullptr);
            }

            vkDestroyBuffer(device, elem.__data.vertexBuffer, nullptr);
            vkFreeMemory(device, elem.__data.vertexBufferMemory, nullptr);
        }

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
