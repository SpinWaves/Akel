// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#ifndef __AK_CORE_ENGINE_CONFIG__
#define __AK_CORE_ENGINE_CONFIG__

#include <Core/PreCompiled.h>
#include <Graphics/Enums.h>

namespace Ak
{
	struct EngineConfig
	{
		std::filesystem::path vfs_root_directory;
		RendererDrivers preffered_render_api = RendererDrivers::Vulkan;
	};
}

#endif
