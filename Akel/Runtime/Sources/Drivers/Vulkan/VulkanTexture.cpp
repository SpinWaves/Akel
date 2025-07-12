// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanTexture.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanInstance.h>

namespace Ak
{
	constexpr std::array ImageFormatToVkFormat{
		VK_FORMAT_UNDEFINED,                   // None
		VK_FORMAT_R8_UNORM,                    // R8_Unorm
		VK_FORMAT_R8G8_UNORM,                  // R8G8_Unorm
		VK_FORMAT_R8G8B8_UNORM,                // R8G8B8_Unorm
		VK_FORMAT_R8G8B8A8_UNORM,              // R8G8B8A8_Unorm
		VK_FORMAT_R8_UINT,                     // R8_UInt
		VK_FORMAT_B10G11R11_UFLOAT_PACK32,     // R11G11B10_Float
		VK_FORMAT_A2B10G10R10_UNORM_PACK32,    // R10G10B10A2_Unorm
		VK_FORMAT_R32_SINT,                    // R32_Int
		VK_FORMAT_R32G32_SINT,                 // R32G32_Int
		VK_FORMAT_R32G32B32_SINT,              // R32G32B32_Int
		VK_FORMAT_R32G32B32A32_SINT,           // R32G32B32A32_Int
		VK_FORMAT_R32_UINT,                    // R32_UInt
		VK_FORMAT_R32G32_UINT,                 // R32G32_UInt
		VK_FORMAT_R32G32B32_UINT,              // R32G32B32_UInt
		VK_FORMAT_R32G32B32A32_UINT,           // R32G32B32A32_UInt
		VK_FORMAT_R16_SFLOAT,                  // R16_Float
		VK_FORMAT_R16G16_SFLOAT,               // R16G16_Float
		VK_FORMAT_R16G16B16_SFLOAT,            // R16G16B16_Float
		VK_FORMAT_R16G16B16A16_SFLOAT,         // R16G16B16A16_Float
		VK_FORMAT_R32_SFLOAT,                  // R32_Float
		VK_FORMAT_R32G32_SFLOAT,               // R32G32_Float
		VK_FORMAT_R32G32B32_SFLOAT,            // R32G32B32_Float
		VK_FORMAT_R32G32B32A32_SFLOAT,         // R32G32B32A32_Float
		VK_FORMAT_D16_UNORM,                   // D16_Unorm
		VK_FORMAT_D32_SFLOAT,                  // D32_Float
		VK_FORMAT_D16_UNORM_S8_UINT,           // D16_Unorm_S8_UInt
		VK_FORMAT_D24_UNORM_S8_UINT,           // D24_Unorm_S8_UInt
		VK_FORMAT_D32_SFLOAT_S8_UINT,          // D32_Float_S8_UInt
	};
	static_assert(ImageFormatToVkFormat.size() == TextureFormatCount, "Missing image formats");

	constexpr std::array ImageTypeToVkImageAspect{
		VK_IMAGE_ASPECT_COLOR_BIT // Color
		VK_IMAGE_ASPECT_DEPTH_BIT // Depth
		 // DepthArray
		 // Cube
		 // Other
	};
	static_assert(ImageFormatToVkFormat.size() == TextureFormatCount, "Missing image formats");

	VulkanTexture::VulkanTexture(SharedPtr<class VulkanDevice> device, TextureType type, TextureFormat format, TextureFlags flags, Vec2ui size, std::uint32_t depth, std::uint8_t level_count)
		: RHITexture(type, format, flags, size, depth, level_count), p_device(device)
	{
	}

	VulkanTexture::VulkanTexture(SharedPtr<class VulkanDevice> device, VkImage image, TextureType type, TextureFormat format, TextureFlags flags, Vec2ui size, std::uint32_t depth, std::uint8_t level_count)
		: RHITexture(type, format, flags, size, depth, level_count), p_device(device), m_image(image)
	{
	}

	void VulkanTexture::CreateImageView(std::uint32_t layer_count)
	{
		Verify(m_image != VK_NULL_HANDLE, "Vulkan: cannot create an image view for a null image");

		VkImageViewCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		create_info.image = m_image;
		create_info.viewType = type;
		create_info.format = ImageFormatToVkFormat[static_cast<std::uint32_t>(m_format)];
		create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.subresourceRange.aspectMask = aspect;
		create_info.subresourceRange.baseMipLevel = 0;
		create_info.subresourceRange.levelCount = m_level_count;
		create_info.subresourceRange.baseArrayLayer = 0;
		create_info.subresourceRange.layerCount = layer_count;
		CheckVk(p_device->vkCreateImageView(p_device->Get(), &create_info, nullptr, &m_image_view));
	}
}
