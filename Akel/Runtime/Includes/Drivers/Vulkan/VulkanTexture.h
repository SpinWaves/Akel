// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_TEXTURE_H
#define AK_VULKAN_TEXTURE_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHITexture.h>
#include <Drivers/Vulkan/Memory/Block.h>

namespace Ak
{
	class AK_VULKAN_API VulkanTexture : public RHITexture
	{
		public:
			VulkanTexture(SharedPtr<class VulkanDevice> device, const TextureDescription& description);
			VulkanTexture(SharedPtr<class VulkanDevice> device, VkImage image, const TextureDescription& description);

			void CreateImageView(std::uint32_t layer_count);

			~VulkanTexture() override;

		private:
			void CreateImage();

		private:
			MemoryBlock m_memory;
			SharedPtr<class VulkanDevice> p_device;
			VkImage m_image = VK_NULL_HANDLE;
			VkImageView m_image_view = VK_NULL_HANDLE;
	};
}

#endif
