// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/04/2024
// Updated : 14/04/2024

#ifndef __AK_DRIVER_WEBGPU_SURFACE_HELPER__
#define __AK_DRIVER_WEBGPU_SURFACE_HELPER__

#include <Drivers/WebGPU/PreCompiled.h>
#include <Platform/SI/WindowBackend.h>

namespace Ak::WebGPU
{
	WGPUSurface CreateSurfaceFromWindowBackend(const WindowBackend& window) noexcept;
}

#endif
