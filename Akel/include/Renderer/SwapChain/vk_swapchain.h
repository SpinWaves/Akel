// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 15/06/2023

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akpch.h>
#include <Renderer/Images/vk_image.h>

namespace Ak
{
	class SwapChain
	{
		friend class GraphicPipeline;
		friend class SceneRenderer;
		friend class DepthImage;

		public:
			struct SwapChainSupportDetails
			{
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};

		public:
			SwapChain() = default;

			void init(class RendererComponent* renderer);
			void recreate();
			void destroy() noexcept;

			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

			inline VkSwapchainKHR get() noexcept { return _swapChain; }
			inline VkSwapchainKHR operator()() noexcept { return _swapChain; }
			inline size_t getImagesNumber() const noexcept { return _images.size(); }
			inline Image& getImage(std::size_t i) noexcept { return _images[i]; }
			inline SwapChainSupportDetails getSupport() noexcept { return _swapChainSupport; }

			~SwapChain() = default;

		private:
			SwapChainSupportDetails _swapChainSupport;
			VkSwapchainKHR _swapChain;
			std::vector<Image> _images;
			VkFormat _swapChainImageFormat;
			VkExtent2D _extent;
			class RendererComponent* _renderer = nullptr;
	};
}

#endif // __AK_VK_SWAPCHAIN__
