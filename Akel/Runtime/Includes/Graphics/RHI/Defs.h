// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 20/02/2024

#ifndef __AK_RHI_DEFS__
#define __AK_RHI_DEFS__

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Enums.h>

namespace Ak
{
	using DeviceSize = std::uint64_t;

	struct BufferDescription
	{
		const void* initial_data = nullptr;
		const char* debug_name = nullptr;
		DeviceSize size;
		BufferUsage usage;
		BufferType type;
	};

	struct TextureDescription
	{
		const void* initial_data = nullptr;
		const char* debug_name = nullptr;
		TextureFormat format;
		TextureType type;
		std::size_t width;
		std::size_t height;
		TextureFlags flags;
	};
}

#endif
