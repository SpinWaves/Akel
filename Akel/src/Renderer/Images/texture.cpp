// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 10/02/2023

#include <Renderer/Images/texture.h>
#include <Renderer/Pipeline/vk_shader.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#define STBI_ASSERT(x) Ak_assert(x, "stb_image assertion failed")
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Ak
{
	void Texture::create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format)
	{
		Image::create(width, height, format,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		Image::createImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
		Image::createSampler();

		Buffer staging_buffer;
		std::size_t size = width * height * (format == VK_FORMAT_R32G32B32A32_SFLOAT ? 16 : 4);
		staging_buffer.create(Buffer::kind::dynamic, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, pixels);
		Image::copyBuffer(staging_buffer);
		staging_buffer.destroy();
	}

	void Texture::setShaderInterface(Shader& shader)
	{
		if(shader.getImageSamplers().count("texSampler"))
		{
			shader.getImageSamplers()["texSampler"].setSampler(Image::getSampler());
			shader.getImageSamplers()["texSampler"].setImageView(Image::getImageView());
		}
	}

	Texture loadTextureFromFile(std::filesystem::path path)
	{
		Texture texture;
		int width;
		int height;
		int channels;
		VkFormat format;
		uint8_t* data = nullptr;
		std::string filename = path.string();

		if(!std::filesystem::exists(std::move(path)))
			Core::log::report(FATAL_ERROR, "Trying to create a texture from unfound file '%s'", filename.c_str());
		if(stbi_is_hdr(filename.c_str()))
		{
			data = (uint8_t*)stbi_loadf(filename.c_str(), &width, &height, &channels, 4);
			format = VK_FORMAT_R32G32B32A32_SFLOAT;
		}
		else
		{
			data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
			format = VK_FORMAT_R8G8B8A8_UNORM;
		}
		texture.create(data, width, height, format);
		stbi_image_free(data);
		return texture;
	}
}
