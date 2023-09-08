// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/09/2023
// Updated : 08/09/2023

#ifndef __AK_LOAD_IMAGE__
#define __AK_LOAD_IMAGE__

#include <Akpch.h>
#include <Core/Memory/memory.h>

namespace Ak
{
	struct ImageData
	{
		std::vector<uint8_t> pixels;
		int width = 0;
		int height = 0;
		uint32_t bits_per_pixel = 0;
		bool is_hdr = false;
	};

	ImageData loadImageFromFile(const std::string& file);
	inline ImageData loadImageFromFile(const std::filesystem::path& file)
	{
		return loadImageFromFile(file.string());
	}
}

#endif
