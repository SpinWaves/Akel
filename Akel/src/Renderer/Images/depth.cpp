// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/01/2023
// Updated : 13/01/2023

#include <Renderer/Images/depth.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void DepthImage::create(RendererComponent& renderer)
	{
		VkFormat format = findSupportedFormat({VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
		Image::create(renderer.getSwapChain()._swapChainExtent.width, renderer.getSwapChain()._swapChainExtent.height, 
				format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				VK_IMAGE_ASPECT_DEPTH_BIT);
	}
}
