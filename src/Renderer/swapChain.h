// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 06/06/2021

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akpch.h>

#include <Renderer/renderPass.h>
#include <Renderer/queues.h>

namespace Ak
{
	struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

	class SwapChain : virtual public RenderPass, public Queues
	{
		public:
            SwapChain();
            void createSwapChain();
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkExtent2D swapChainExtent;
            std::vector<VkFramebuffer> swapChainFramebuffers;
	};
}

#endif // __AK_VK_SWAPCHAIN__

