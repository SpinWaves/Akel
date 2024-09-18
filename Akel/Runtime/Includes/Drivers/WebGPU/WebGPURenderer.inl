// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Drivers/WebGPU/WebGPURenderer.h>

#include <Core/Logs.h>

namespace Ak
{
	WebGPUDevice& WebGPURenderer::GetDevice(std::uint32_t index)
	{
		return *p_device;
	}

	WebGPUInstance& WebGPURenderer::GetInstance()
	{
		Verify((bool)p_instance, "WebGPU Renderer : cannot get WebGPU instance as the renderer is not init");
		return *p_instance;
	}
}
