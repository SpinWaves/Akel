// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 29/06/2021

#include <Renderer/renderer.h>
#include <Core/core.h>

namespace Ak
{
	CommandBuffer::CommandBuffer() : Pipeline() {}

    void CommandBuffer::createCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create command pool");
    }

    void CommandBuffer::createCommandBuffers()
    {
        commandBuffers.resize(swapChainFramebuffers.size());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

        if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to allocate command buffer");

        for(size_t i = 0; i < commandBuffers.size(); i++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
				Core::log::report(FATAL_ERROR, "Vulkan : Failed to begin recording command buffer");

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;

            VkClearValue clearColor = {1.0f, 0.0f, 1.0f, 1.0f};
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

                vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
                vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);

            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				Core::log::report(FATAL_ERROR, "Vulkan : Failed to begin record command buffer");
        }
    }
}

