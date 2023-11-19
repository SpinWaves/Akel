// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 19/11/2023

#include <Renderer/Core/render_core.h>
#include <Renderer/Images/cubemap.h>
#include <Core/log.h>
#include <Renderer/Buffers/vk_buffer.h>
#include <Utils/load_image.h>

namespace Ak
{
	void Cubemap::create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format, int nlayers)
	{
		Image::create(width, height, format,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					VK_IMAGE_LAYOUT_UNDEFINED, true);

		Image::createImageView(VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_ASPECT_COLOR_BIT);
		Image::createSampler();

		CmdPool pool;
		pool.init();
		CmdBuffer cmd;
		cmd.init(&pool);

		if(pixels == nullptr)
		{
			transitionLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, cmd);
			return;
		}

		size_t data_size = width * height * RCore::formatSize(format) * 6;
		std::vector<uint8_t> data(data_size);
		std::memcpy(data.data(), pixels, data_size);
		Buffer staging_buffer;
		staging_buffer.create(Buffer::kind::dynamic, data_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, pixels);
		std::vector<VkBufferImageCopy> bufferCopyRegions;
		uint32_t offset = 0;

		for(uint32_t face = 0; face < nlayers; face++)
		{
			VkBufferImageCopy bufferCopyRegion = {};
			bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			bufferCopyRegion.imageSubresource.mipLevel = 0;
			bufferCopyRegion.imageSubresource.baseArrayLayer = face;
			bufferCopyRegion.imageSubresource.layerCount = 1;
			bufferCopyRegion.imageExtent.width = width;
			bufferCopyRegion.imageExtent.height = height;
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
		cmd.destroy();
		pool.destroy();
	}

	Cubemap loadCubemapFromFile(const std::filesystem::path& file)
	{
		Cubemap cubemap;
		ImageData data = loadImageFromFile(file);

		std::array<std::vector<uint8_t>, 6> cubeTextureData;

		uint32_t faceWidth = data.width / 3;
		uint32_t faceHeight = data.height / 4;
		uint32_t face = 0;
		uint32_t size = 0;

		for(uint32_t cy = 0; cy < 4; cy++)
		{
			for(uint32_t cx = 0; cx < 3; cx++)
			{
				if((cy == 0 || cy == 2 || cy == 3) && cx != 1)
					continue;

				uint32_t stride = data.bits_per_pixel / 8;

				cubeTextureData[face].resize(faceWidth * faceHeight * stride);
				size += stride * data.width * data.height;

				for(uint32_t y = 0; y < faceHeight; y++)
				{
					uint32_t offset = y;
					if(face == 5)
						offset = faceHeight - (y + 1);
					uint32_t yp = cy * faceHeight + offset;
					for(uint32_t x = 0; x < faceWidth; x++)
					{
						offset = x;
						if(face == 5)
							offset = faceWidth - (x + 1);
						uint32_t xp = cx * faceWidth + offset;
						cubeTextureData[face][(x + y * faceWidth) * stride + 0] = data.pixels[(xp + yp * data.width) * stride + 0];
						cubeTextureData[face][(x + y * faceWidth) * stride + 1] = data.pixels[(xp + yp * data.width) * stride + 1];
						cubeTextureData[face][(x + y * faceWidth) * stride + 2] = data.pixels[(xp + yp * data.width) * stride + 2];
						if(stride >= 4)
							cubeTextureData[face][(x + y * faceWidth) * stride + 3] = data.pixels[(xp + yp * data.width) * stride + 3];
					}
				}
			}
			face++;
		}
		std::unique_ptr<uint8_t[]> allData(new uint8_t[size]);
		uint32_t pointeroffset = 0;
		constexpr const uint8_t faceOrder[6] = { 3, 1, 0, 4, 2, 5 };
		for(uint8_t face = 0; face < 6; face++)
		{
			uint32_t currentSize = faceWidth * faceHeight * (data.bits_per_pixel / 8);
			std::cout << currentSize << "	" << cubeTextureData[faceOrder[face]].size() << std::endl;
			if(cubeTextureData[faceOrder[face]].size() == 0)
				break;
			std::memcpy(allData.get() + pointeroffset, cubeTextureData[faceOrder[face]].data(), currentSize);
			pointeroffset += currentSize;
		}
		cubemap.create(allData.get(), data.width, data.height, bitsToFormat(data.bits_per_pixel), 6);
		return cubemap;
	}
}
