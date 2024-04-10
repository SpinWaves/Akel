// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#pragma once
#include <Drivers/WebGPU/WebGPURenderer.h>

#include <Core/Logs.h>

namespace Ak
{
	WebGPUDevice& WebGPURenderer::GetDevice()
	{
		return *p_device;
	}

	WebGPUInstance& WebGPURenderer::GetInstance()
	{
		Verify((bool)p_instance, "WebGPU Renderer : cannot get WebGPU instance as the renderer is not init");
		return *p_instance;
	}
}
