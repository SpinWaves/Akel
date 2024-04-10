// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#include <Drivers/WebGPU/WebGPURenderer.h>
#include <Drivers/WebGPU/WebGPUDevice.h>

namespace Ak
{
	WebGPUDevice::WebGPUDevice()
	{
	}

	void WebGPUDevice::SelectAdapter() noexcept
	{
		struct UserData
		{
			WGPUAdapter* adapter = nullptr;
			bool request_ended = false;
		};
		UserData user_data;
		user_data.adapter = m_adapter;

		wgpuInstanceRequestAdapter(WebGPURenderer::GetInstance(), options,
		onAdapterRequestEnded,
		(void*)&user_data);
	}

	WebGPUDevice::~WebGPUDevice()
	{
	}
}
