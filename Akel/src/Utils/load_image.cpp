// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/09/2023
// Updated : 07/09/2023

#include <Core/vfs.h>
#include <Core/log.h>
#include <Utils/load_image.h>
#include <Utils/assert.h>
#define STBI_ASSERT(x) Ak_assert(x, "stb_image assertion failed")
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Ak
{
	ImageData loadImageFromFile(const std::string& file)
	{
		std::filesystem::path path = VFS::resolve(file);

		if(!std::filesystem::exists(path))
			Core::log::report(FATAL_ERROR, "Image Loader : file not found '%s'", file.c_str());
		
		uint8_t* tmp = nullptr;
		int channels = 0;
		int size_of_channel = 8;
		ImageData data;

		if(stbi_is_hdr(path.string().c_str()))
		{
			tmp = (uint8_t*)stbi_loadf(path.string().c_str(), &data.width, &data.height, &channels, 4);
			data.is_hdr = true;
			size_of_channel = 32;
		}
		else
		{
			tmp = stbi_load(path.string().c_str(), &data.width, &data.height, &channels, 4);
			data.is_hdr = false;
		}

		if(!tmp)
		{
			channels = 4;

			data.width = 2;
			data.height = 2;
			data.bits_per_pixel = channels * size_of_channel;		
			const int32_t size = data.width * data.height * channels;
			data.pixels = memAlloc<uint8_t>(size);

			uint8_t datatwo[16] = {
				255, 0, 255, 255,
				0, 0, 0, 255,
				0, 0, 0, 255,
				255, 0, 255, 255
			};

			std::memcpy(data.pixels, datatwo, size);

			return data;
		}
		if(channels != 4)
			channels = 4;

		data.bits_per_pixel = channels * size_of_channel;		
		const int32_t size = data.width * data.height * channels * size_of_channel / 8;
		data.pixels = memAlloc<uint8_t>(size);
		std::memcpy(data.pixels, tmp, size);
		stbi_image_free(tmp);
		return data;
	}
}
