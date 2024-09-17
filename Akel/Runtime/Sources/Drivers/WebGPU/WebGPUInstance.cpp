// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/Logs.h>
#include <Drivers/WebGPU/WebGPUInstance.h>

namespace Ak
{
	WebGPUInstance::WebGPUInstance()
	{
		WGPUInstanceDescriptor desc{};
		desc.nextInChain = nullptr;
		m_instance = wgpuCreateInstance(&desc);
		if(m_instance == nullptr)
			FatalError("WebGPU : failed to create WebGPU instance");
		DebugLog("WebGPU : created new instance");
	}

	WebGPUInstance::~WebGPUInstance()
	{
		wgpuInstanceRelease(m_instance);
		m_instance = nullptr;
		DebugLog("WebGPU : destroyed an instance");
	}
}
