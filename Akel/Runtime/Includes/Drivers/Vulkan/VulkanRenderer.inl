// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/05/2024

#pragma once
#include <Drivers/Vulkan/VulkanRenderer.h>

#include <Core/Logs.h>
#include <Utils/CallOnExit.h>

namespace Ak
{
	VulkanDevice& VulkanRenderer::GetDevice()
	{
		return *p_device;
	}
/*
	VulkanInstance& VulkanRenderer::GetInstance()
	{
		Verify((bool)p_instance, "Vulkan Renderer : cannot get Vulkan instance as the renderer is not init");
		return *p_instance;
	}
*/
	bool IsVulkanSupported() noexcept
	{
		if(volkInitialize() != VK_SUCCESS)
			return false;

		CallOnExit uninit_volk(volkFinalize);

		VkInstance instance;
		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		VkResult res;
		if(vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
			return false;
		return true;
	}
}
