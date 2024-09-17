// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
		user_data.adapter = &m_adapter;

		//wgpuInstanceRequestAdapter(WebGPURenderer::GetInstance(), options,
		//onAdapterRequestEnded,
		//(void*)&user_data);
	}

	WebGPUDevice::~WebGPUDevice()
	{
	}
}
