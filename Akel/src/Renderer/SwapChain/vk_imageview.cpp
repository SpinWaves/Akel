// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 21/12/2022

#include "vk_swapchain.h"
#include "vk_imageview.h"
#include <Renderer/Core/render_core.h>
#include <Core/core.h>
#include <Utils/assert.h>

namespace Ak
{
	void ImageView::init(SwapChain& swapchain, VkImage& image)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = image;
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapchain._swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if(vkCreateImageView(Render_Core::get().getDevice().get(), &createInfo, nullptr, &_image) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create an image view");
	}
	
	void ImageView::destroy() noexcept
	{
		Ak_assert(_image != VK_NULL_HANDLE, "trying to destroy an uninit image view");
		vkDestroyImageView(Render_Core::get().getDevice().get(), _image, nullptr);
	}
}
