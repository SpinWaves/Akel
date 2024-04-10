// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

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
