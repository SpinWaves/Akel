// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

#pragma once
#include <Drivers/Vulkan/VulkanRenderer.h>

#include <Core/Logs.h>

namespace Ak
{
	VulkanDevice& VulkanRenderer::GetDevice()
	{
		return *m_device;
	}

	VulkanInstance& VulkanRenderer::GetInstance()
	{
		Verify((bool)m_instance, "Vulkan Renderer : cannot get Vulkan instance as the renderer is not init");
		return *m_instance;
	}
}
