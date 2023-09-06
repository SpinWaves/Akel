// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/09/2023
// Updated : 06/09/2023

#ifndef __AK_LOAD_IMAGE__
#define __AK_LOAD_IMAGE__

#include <Akpch.h>
#include <Core/Memory/memory.h>

namespace Ak
{
	struct ImageData
	{
		uint8_t* pixels = nullptr;
		size_t width = 0;
		size_t height = 0;
		uint32_t bits_per_pixels = 0;
		bool is_hdr = false;

		~ImageData()
		{
			memFree(pixels);
		}
	};

	ImageData loadImageFromFile(const std::string& file);
	inline ImageData loadImageFromFile(const std::filesystem::path& file)
	{
		return loadImageFromFile(file.string());
	}
}

#endif
