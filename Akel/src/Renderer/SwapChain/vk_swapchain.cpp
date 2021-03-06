// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 05/07/2022

#include <Renderer/Core/render_core.h>
#include <Platform/window.h>

namespace Ak
{
    void SwapChain::init()
    {
        _swapChainSupport = querySwapChainSupport(Render_Core::get().getDevice().getPhysicalDevice());

        VkSurfaceFormatKHR surfaceFormat = Render_Core::get().getSurface().chooseSwapSurfaceFormat(_swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(_swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(_swapChainSupport.capabilities);

        uint32_t imageCount = _swapChainSupport.capabilities.minImageCount + 1;
        if(_swapChainSupport.capabilities.maxImageCount > 0 && imageCount > _swapChainSupport.capabilities.maxImageCount)
            imageCount = _swapChainSupport.capabilities.maxImageCount;

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = Render_Core::get().getSurface().get();

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().findQueueFamilies(Render_Core::get().getDevice().getPhysicalDevice());
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if(indices.graphicsFamily != indices.presentFamily)
		{
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
		else
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

        createInfo.preTransform = _swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkDevice device = Render_Core::get().getDevice().get();

        if(vkCreateSwapchainKHR(device, &createInfo, nullptr, &_swapChain) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create swapchain");

        vkGetSwapchainImagesKHR(device, _swapChain, &imageCount, nullptr);
        _swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, _swapChain, &imageCount, _swapChainImages.data());

        _swapChainImageFormat = surfaceFormat.format;
        _swapChainExtent = extent;

        _imageViews.resize(_swapChainImages.size());

        for(size_t i = 0; i < _swapChainImages.size(); i++)
        {
            _imageViews[i] = memAlloc<ImageView>();
            _imageViews[i]->init(this, _swapChainImages[i]);
        }
    }

    void SwapChain::initFB()
    {
        _framebuffers.resize(_imageViews.size());

        for(size_t i = 0; i < _imageViews.size(); i++)
        {
            _framebuffers[i] = memAlloc<FrameBuffer>();
            _framebuffers[i]->init(this, *_imageViews[i]);
        }
    }

    SwapChain::SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice device)
    {
        SwapChain::SwapChainSupportDetails details;
        VkSurfaceKHR surface = Render_Core::get().getSurface().get();

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if(formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if(presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkPresentModeKHR SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
		if(!Render_Core::get().getWindow()->vsync)
		    return VK_PRESENT_MODE_IMMEDIATE_KHR;

        for(const auto& availablePresentMode : availablePresentModes)
        {
            if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                return availablePresentMode;
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
            return capabilities.currentExtent;

        int width, height;
        SDL_Vulkan_GetDrawableSize(Render_Core::get().getWindow()->getNativeWindow(), &width, &height);

        VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void SwapChain::recreate()
    {
        destroyFB();
        destroy();
        Render_Core::get().getRenderPass().destroy();

        init();
        Render_Core::get().getRenderPass().init();
        initFB();
    }

    void SwapChain::destroyFB() noexcept
    {
        if(_framebuffers[0] == nullptr)
            return;

        vkDeviceWaitIdle(Render_Core::get().getDevice().get());
            
        for(size_t i = 0; i < _framebuffers.size(); i++)
        {
            _framebuffers[i]->destroy();
            memFree(_framebuffers[i]);
            _framebuffers[i] = nullptr;
        }
    }

    void SwapChain::destroy() noexcept
    {
        if(_swapChain == VK_NULL_HANDLE && _imageViews[0] == nullptr)
            return;
        
        vkDeviceWaitIdle(Render_Core::get().getDevice().get());

        for(size_t i = 0; i < _imageViews.size(); i++)
        {
            _imageViews[i]->destroy();
            memFree(_imageViews[i]);
            _imageViews[i] = nullptr;
        }

        if(_swapChain != VK_NULL_HANDLE)
            vkDestroySwapchainKHR(Render_Core::get().getDevice().get(), _swapChain, nullptr);
        _swapChain = VK_NULL_HANDLE;
    }
}
