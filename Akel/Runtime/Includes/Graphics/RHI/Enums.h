// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 19/02/2024

#ifndef __AK_RHI_ENUMS__
#define __AK_RHI_ENUMS__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	enum class BufferType
	{
		Constant = 0,
		HighDynamic, // typically stored in RAM
		LowDynamic,  // typically stored in VRAM

		EndEnum
	};
	constexpr std::size_t BufferTyoeCount = static_cast<std::size_t>(BufferType::EndEnum) + 1;

	enum BufferUsageBits
	{
		BufferUsageTransferSrc = 1 << 0,
		BufferUsageTransferDst = 1 << 1,
		BufferUsageVertex = 1 << 2,
		BufferUsageIndex = 1 << 3,
		BufferUsageUniform = 1 << 4,
		BufferUsageStorage = 1 << 5
	};
	constexpr std::size_t BufferUsageCount = 6;
	using BufferUsage = std::uint32_t;
}

#endif
