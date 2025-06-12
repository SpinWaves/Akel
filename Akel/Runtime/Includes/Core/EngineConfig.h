// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_ENGINE_CONFIG_H
#define AK_CORE_ENGINE_CONFIG_H

#include <Core/PreCompiled.h>
#include <Graphics/Enums.h>

namespace Ak
{
	struct EngineConfig
	{
		std::filesystem::path vfs_root_directory;
		RendererDrivers preffered_render_api = RendererDrivers::Auto;
	};
}

#endif
