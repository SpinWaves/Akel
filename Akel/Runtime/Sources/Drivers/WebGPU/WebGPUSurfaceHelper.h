// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_DRIVER_WEBGPU_SURFACE_HELPER__
#define __AK_DRIVER_WEBGPU_SURFACE_HELPER__

#include <Drivers/WebGPU/PreCompiled.h>
#include <Platform/SI/WindowBackend.h>

namespace Ak::WebGPU
{
	WGPUSurface CreateSurfaceFromWindowBackend(const WindowBackend& window) noexcept;
}

#endif