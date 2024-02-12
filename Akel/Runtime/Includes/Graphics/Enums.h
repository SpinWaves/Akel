// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2024
// Updated : 12/02/2024

#ifndef __AK_GRAPHICS_ENUMS__
#define __AK_GRAPHICS_ENUMS__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	enum class RenderBackend
	{
		Vulkan = 0,
		// OpenGL ?
		// WebGPU ?
		// Dx12 ?

		EndEnum
	};
	constexpr std::size_t RenderBackendCount = static_cast<std::size_t>(RenderBackend::EndEnum) + 1;
}

#endif
