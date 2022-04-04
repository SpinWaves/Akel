// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 04/04/2022

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akcph.h>
#include <vk_framebuffer.h>

namespace Ak
{
    class SwapChain
    {
        public:
            struct SwapChainSupportDetails
            {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentModes;
            };

            void init();
            void destroy();

            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        private:
            VkSwapchainKHR _swapChain;
            std::vector<VkImage> _swapChainImages;
            VkFormat _swapChainImageFormat;
            VkExtent2D _swapChainExtent;
            std::vector<FrameBuffer> _framebuffers;
    };
}

#endif // __AK_VK_SWAPCHAIN__
