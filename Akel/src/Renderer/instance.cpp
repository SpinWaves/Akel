// This file is a part of Akel
// CREATED : 10/04/2021
// UPDATED : 26/09/2021

#include <Renderer/instance.h>
#include <Platform/platform.h>
#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
	Instance::Instance() : CommandBuffer(), ValidationLayers() {}

    void Instance::init(SDL_Window* win, const char* vertexShader, const char* fragmentShader)
    {
        window = win;

		const std::vector<Vertex> vertices =
		{
		    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
		};

		const std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline(vertexShader, fragmentShader);
        createFramebuffers();
        createCommandPool();
        createVertexBuffer(vertices);
        createIndexBuffer(indices);
        createCommandBuffers();
        createSemaphores();

		_instanceInitialized = true;
    }

	void Instance::setVsync(bool setter)
	{
		enableVsync = setter;
	}

	bool Instance::getVsync()
	{
		return enableVsync;
	}

    std::vector<const char*> Instance::getRequiredExtensions()
    {
        unsigned int count;
        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
			Core::log::report(ERROR, std::string("Vulkan : Cannot get instance extentions from window : ") + SDL_GetError());

        std::vector<const char*> extensions = {
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME // Sample additional extension
        };
        size_t additional_extension_count = extensions.size();
        extensions.resize(additional_extension_count + count);

        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count))
			Core::log::report(ERROR, std::string("Vulkan : Cannot get instance extentions from window : ") + SDL_GetError());

        if(enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }


    void Instance::createInstance()
    {
        if(enableValidationLayers && !checkValidationLayerSupport())
			Core::log::report(ERROR, "Vulkan : Layer validations are enabled but not available");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = SDL_GetWindowTitle(window);
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Akel";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if(enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create Vulkan instance");
    }

    void Instance::render()
    {
		if(!_instanceInitialized)
			Core::log::report(FATAL_ERROR, "Vulkan : unable to render, you need to init the instance before");
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

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


    void Instance::cleanup()
    {
        for(auto framebuffer : swapChainFramebuffers)
            vkDestroyFramebuffer(device, framebuffer, nullptr);

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for(auto imageView : swapChainImageViews)
            vkDestroyImageView(device, imageView, nullptr);

        vkDestroySwapchainKHR(device, swapChain, nullptr);

        cleanupBuffers();

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
