// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Drivers/Vulkan/VulkanRenderer.h>

#include <Core/Logs.h>
#include <Utils/CallOnExit.h>

namespace Ak
{
	VulkanDevice& VulkanRenderer::GetDevice(std::uint32_t index)
	{
		try
		{
			return m_devices.at(index);
		}
		catch(...)
		{
			FatalError("Vulkan Renderer : invalid device index");
		}
	}

	VulkanInstance& VulkanRenderer::GetInstance()
	{
		return *p_instance;
	}

	bool VulkanRenderer::IsInit() noexcept
	{
		return s_instance != nullptr;
	}

	VulkanRenderer& VulkanRenderer::Get() noexcept
	{
		Assert(IsInit(), "VulkanRenderer is not initialized");
		return *s_instance;
	}

	bool IsVulkanSupported() noexcept
	{
		// TODO
		return true;
	}
}
