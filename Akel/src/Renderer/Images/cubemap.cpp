// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 06/09/2023

#include <Renderer/Core/render_core.h>
#include <Renderer/Images/cubemap.h>
#include <Core/log.h>
#include <Renderer/Buffers/vk_buffer.h>
#include <Utils/load_image.h>

namespace Ak
{
	void Cubemap::create(uint8_t* pixels, uint32_t size, VkFormat format)
	{
		Image::create(size, size, format,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VK_IMAGE_LAYOUT_UNDEFINED, true);

		Image::createImageView(VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_ASPECT_COLOR_BIT);
		Image::createSampler();
		
		CmdPool pool;
		pool.init();
		CmdBuffer cmd;
		cmd.init(&pool);

		if(pixels != nullptr)
		{
			size_t data_size = size * size * RCore::formatSize(format) * 6;
			std::vector<uint8_t> data(data_size);
			std::memcpy(data.data(), pixels, data_size);
			Buffer staging_buffer;
			staging_buffer.create(Buffer::kind::dynamic, data_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, pixels);
			std::vector<VkBufferImageCopy> bufferCopyRegions;
			uint32_t offset = 0;

			for(uint32_t face = 0; face < 6; face++)
			{
				VkBufferImageCopy bufferCopyRegion = {};
				bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				bufferCopyRegion.imageSubresource.mipLevel = 0;
				bufferCopyRegion.imageSubresource.baseArrayLayer = face;
				bufferCopyRegion.imageSubresource.layerCount = 1;
				bufferCopyRegion.imageExtent.width = size;
				bufferCopyRegion.imageExtent.height = size;
				bufferCopyRegion.imageExtent.depth = 1;
				bufferCopyRegion.bufferOffset = offset;
				bufferCopyRegions.push_back(bufferCopyRegion);

				offset += width * height * RCore::formatSize(format);
			}

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = 1;
			subresourceRange.layerCount = 1;

			transitionLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, cmd, false);
			vkCmdCopyBufferToImage(cmd.get(), staging_buffer.get(), Image::get(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(bufferCopyRegions.size()), bufferCopyRegions.data());
			transitionLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, cmd);

			staging_buffer.destroy();
		}
		else
			transitionLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, cmd);
		cmd.destroy();
		pool.destroy();
	}

	Cubemap loadCubemapFromFile(const std::filesystem::path& file)
	{
		Cubemap cubemap;
		ImageData data = loadImageFromFile(file);
		cubemap.create();
		return cubemap;
	}
}
