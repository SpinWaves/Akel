// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 07/12/2022

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akpch.h>
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
		friend class Scene;

        public:
            struct SwapChainSupportDetails
            {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentModes;
            };

            void init();
            void initFB();
            void destroy() noexcept;
            void destroyFB() noexcept;

            void recreate();

            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            inline SwapChainSupportDetails getSupport() noexcept { return _swapChainSupport; }
            inline VkSwapchainKHR& operator()() noexcept { return _swapChain; }
            inline VkSwapchainKHR& get() noexcept { return _swapChain; }
            inline FrameBuffer& getFrameBuffer(int i) { return *_framebuffers[i]; }
            inline size_t getImagesNumber() const noexcept { return _swapChainImages.size(); }

        private:
            SwapChainSupportDetails _swapChainSupport;
            VkSwapchainKHR _swapChain;
            std::vector<VkImage> _swapChainImages;
            VkFormat _swapChainImageFormat;
            VkExtent2D _swapChainExtent;
            std::vector<FrameBuffer*> _framebuffers;
            std::vector<ImageView*> _imageViews;
    };
}

#endif // __AK_VK_SWAPCHAIN__
