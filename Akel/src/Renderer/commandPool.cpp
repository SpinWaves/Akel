// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2022
// Updated : 28/03/2022

#include "commandPool.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	CommandPool::CommandPool(const std::thread::id& threadId) : _threadId(threadId)
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();
		auto graphicsFamily = logicalDevice->getGraphicsFamily();

		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		commandPoolCreateInfo.queueFamilyIndex = graphicsFamily;
		RCore::checkVk(vkCreateCommandPool(*logicalDevice, &commandPoolCreateInfo, nullptr, &commandPool));
	}

	CommandPool::~CommandPool()
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();
		vkDestroyCommandPool(*logicalDevice, commandPool, nullptr);
	}
}
