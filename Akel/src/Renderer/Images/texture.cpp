// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 19/11/2023

#include <Renderer/Images/texture.h>
#include <Renderer/Pipeline/vk_shader.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Command/vk_cmd_pool.h>
#include <Renderer/Command/vk_cmd_buffer.h>
#include <Utils/load_image.h>

namespace Ak
{
	void Texture::create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format)
	{
		Image::create(width, height, format,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);

		Image::createImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
		Image::createSampler();

		if(pixels != nullptr)
		{
			Buffer staging_buffer;
			std::size_t size = width * height * RCore::formatSize(format);
			staging_buffer.create(Buffer::kind::dynamic, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, pixels);
			Image::copyBuffer(staging_buffer);
			staging_buffer.destroy();
		}
		CmdPool pool;
		pool.init();
		CmdBuffer cmd;
		cmd.init(&pool);
		if(pixels == nullptr)
			transitionLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, cmd);
		else
			transitionLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, cmd);
		cmd.destroy();
		pool.destroy();
	}

	Texture loadTextureFromFile(std::filesystem::path path)
	{
		ImageData data = loadImageFromFile(std::move(path));
		Texture texture;
		texture.create(data.pixels.data(), data.width, data.height, bitsToFormat(data.bits_per_pixel));
		return texture;
	}
}
