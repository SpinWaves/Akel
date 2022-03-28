// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2022
// Updated : 28/03/2022

#ifndef __AK_VK_SWAPCHAIN__
#define __AK_VK_SWAPCHAIN__

#include <Akpch.h>

namespace Ak
{
	class Swapchain
	{
		public:
			explicit Swapchain(const VkExtent2D& extent, const Swapchain* oldSwapchain = nullptr);

			VkResult acquireNextImage(const VkSemaphore& presentCompleteSemaphore = VK_NULL_HANDLE, VkFence fence = VK_NULL_HANDLE);
			VkResult queuePresent(const VkQueue& presentQueue, const VkSemaphore& waitSemaphore = VK_NULL_HANDLE);

			inline bool isSameExtent(const VkExtent2D& extent2D) noexcept { return _extent.width == extent2D.width && _extent.height == extent2D.height; }

			operator const VkSwapchainKHR& () const { return _swapchain; }

			inline const VkExtent2D& getExtent() const noexcept { return _extent; }
			inline uint32_t getImageCount() const noexcept { return _imageCount; }
			inline VkSurfaceTransformFlagsKHR getPreTransform() const noexcept { return _preTransform; }
			inline VkCompositeAlphaFlagBitsKHR getCompositeAlpha() const noexcept { return _compositeAlpha; }
			inline const std::vector<VkImage>& getImages() const noexcept { return _images; }
			inline const VkImage& getActiveImage() const noexcept { return _images[activeImageIndex]; }
			inline const std::vector<VkImageView>& getImageViews() const noexcept { return _imageViews; }
			inline const VkSwapchainKHR& getSwapchain() const noexcept { return _swapchain; }
			inline uint32_t getActiveImageIndex() const noexcept { return _activeImageIndex; }

			~Swapchain();

		private:
			VkExtent2D _extent;
			VkPresentModeKHR _presentMode;

			uint32_t _imageCount = 0;
			VkSurfaceTransformFlagsKHR _preTransform;
			VkCompositeAlphaFlagBitsKHR _compositeAlpha;
			std::vector<VkImage> _images;
			std::vector<VkImageView> _imageViews;
			VkSwapchainKHR _swapchain = VK_NULL_HANDLE;

			VkFence _fenceImage = VK_NULL_HANDLE;
			uint32_t _activeImageIndex = 0;
	};
}

#endif // __AK_VK_SWAPCHAIN__
