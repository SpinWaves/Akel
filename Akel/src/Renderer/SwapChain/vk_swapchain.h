// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 11/04/2022

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akcph.h>
#include "vk_imageview.h"
#include "vk_framebuffer.h"

namespace Ak
{
    class SwapChain
    {
        friend class FrameBuffer;
        friend class ImageView;
        friend class GraphicPipeline;
        friend class RenderPass;

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

            inline VkSwapchainKHR& operator()() const noexcept { return _swapChain; }
            inline VkSwapchainKHR& get() const noexcept { return _swapChain; }
            inline std::vector<FrameBuffer>& getFrameBuffers() const { return _framebuffers; }

        private:
            VkSwapchainKHR _swapChain;
            std::vector<VkImage> _swapChainImages;
            VkFormat _swapChainImageFormat;
            VkExtent2D _swapChainExtent;
            std::vector<FrameBuffer> _framebuffers;
            std::vector<ImageView> _imageViews;
    };
}

#endif // __AK_VK_SWAPCHAIN__
