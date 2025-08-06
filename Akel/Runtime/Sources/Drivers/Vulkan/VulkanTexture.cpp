// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanTexture.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanInstance.h>

namespace Ak
{
	constexpr std::array TextureFormatToVkFormat{
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
	static_assert(TextureFormatToVkFormat.size() == TextureFormatCount, "Missing texture formats");

	constexpr std::array TextureDimensionToVkImageViewType{
		VK_IMAGE_VIEW_TYPE_2D,       // Two
		VK_IMAGE_VIEW_TYPE_2D_ARRAY, // TwoArray
		VK_IMAGE_VIEW_TYPE_3D,       // Three
		VK_IMAGE_VIEW_TYPE_CUBE,     // Cubemap
	};
	static_assert(TextureDimensionToVkImageViewType.size() == TextureDimensionCount, "Missing texture dimensions");

	
	static inline bool IsDepthFormat(TextureFormat format)
	{
		switch(format)
		{
			case TextureFormat::D16_Unorm:
			case TextureFormat::D32_Float:
			case TextureFormat::D16_Unorm_S8_UInt:
			case TextureFormat::D24_Unorm_S8_UInt:
			case TextureFormat::D32_Float_S8_UInt:
				return true;

			default: return false;
		}
	}

	static inline bool IsStencilFormat(TextureFormat format)
	{
		switch(format)
		{
			case TextureFormat::D16_Unorm_S8_UInt:
			case TextureFormat::D24_Unorm_S8_UInt:
			case TextureFormat::D32_Float_S8_UInt:
				return true;

			default: return false;
		}
	}

	VulkanTexture::VulkanTexture(SharedPtr<class VulkanDevice> device, const TextureDescription& description)
		: RHITexture(description), p_device(device)
	{
		CreateImage();
	}

	VulkanTexture::VulkanTexture(SharedPtr<class VulkanDevice> device, VkImage image, const TextureDescription& description)
		: RHITexture(description), p_device(device), m_image(image)
	{
	}

	void VulkanTexture::CreateImage()
	{
		std::uint32_t layer_count = (m_dims == TextureDimension::Three) ? 1 : m_depth;
		std::uint32_t depth = (m_dims == TextureDimension::Three) ? m_depth : 1;

		VkImageCreateFlags flags = 0;
		if(m_dims == TextureDimension::Cubemap)
			flags |= VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
		else if(m_dims == TextureDimension::Three)
			flags |= VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT;

		VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		if(m_usage & (TextureUsageSampled | TextureUsageStorageRead))
			usage |= VK_IMAGE_USAGE_SAMPLED_BIT;
		if(m_usage & TextureUsageColorTarget)
			usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		if(m_usage & TextureUsageDepthStencil)
			usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		if(m_usage & TextureUsageStorageWrite)
			usage |= VK_IMAGE_USAGE_STORAGE_BIT;

		VkImageCreateInfo image_create_info{};
		image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_create_info.imageType = m_dims == TextureDimension::Three ? VK_IMAGE_TYPE_3D : VK_IMAGE_TYPE_2D;
		image_create_info.extent.width = m_size.x;
		image_create_info.extent.height = m_size.y;
		image_create_info.extent.depth = depth;
		image_create_info.mipLevels = 1;
		image_create_info.arrayLayers = layer_count;
		image_create_info.format = TextureFormatToVkFormat[static_cast<std::uint32_t>(m_format)];
		image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		image_create_info.usage = usage;
		image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		image_create_info.flags = flags;
		CheckVk(p_device->vkCreateImage(p_device->Get(), &image_create_info, nullptr, &m_image));

		VkMemoryRequirements mem_requirements;
		p_device->vkGetImageMemoryRequirements(p_device->Get(), m_image, &mem_requirements);

		// There is no defined case where we want texture to be stored outside of VRAM
		VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		m_memory = p_device->GetAllocator().Allocate(mem_requirements.size, mem_requirements.alignment, *p_device->GetAllocator().FindMemoryType(mem_requirements.memoryTypeBits, properties, true));
		p_device->vkBindImageMemory(p_device->Get(), m_image, m_memory.memory, m_memory.offset);
	}

	void VulkanTexture::CreateImageView(std::uint32_t layer_count)
	{
		Verify(m_image != VK_NULL_HANDLE, "Vulkan: cannot create an image view for a null image");

		VkImageAspectFlags aspect_flags = 0;

		if(IsDepthFormat(m_format))
		{
			aspect_flags = VK_IMAGE_ASPECT_DEPTH_BIT;
			if(IsStencilFormat(m_format))
				aspect_flags |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
		else
			aspect_flags = VK_IMAGE_ASPECT_COLOR_BIT;

		VkImageViewCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		create_info.image = m_image;
		create_info.viewType = TextureDimensionToVkImageViewType[static_cast<std::uint32_t>(m_dims)];
		create_info.format = TextureFormatToVkFormat[static_cast<std::uint32_t>(m_format)];
		create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.subresourceRange.aspectMask = aspect_flags;
		create_info.subresourceRange.baseMipLevel = 0;
		create_info.subresourceRange.levelCount = m_level_count;
		create_info.subresourceRange.baseArrayLayer = 0;
		create_info.subresourceRange.layerCount = layer_count;
		CheckVk(p_device->vkCreateImageView(p_device->Get(), &create_info, nullptr, &m_image_view));
	}

	VulkanTexture::~VulkanTexture()
	{
		if(m_image_view != VK_NULL_HANDLE)
			p_device->vkDestroyImageView(p_device->Get(), m_image_view, nullptr);
		if(m_image != VK_NULL_HANDLE)
			p_device->vkDestroyImage(p_device->Get(), m_image, nullptr);
	}
}
