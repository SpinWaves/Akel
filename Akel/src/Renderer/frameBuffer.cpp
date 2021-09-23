// This file is a part of Akel
// CREATED : 06/06/2021
// UPDATED : 23/09/2021

#include <Renderer/frameBuffer.h>
#include <Core/core.h>

namespace Ak
{
	FrameBuffer::FrameBuffer() : SwapChain() {}

    void FrameBuffer::createFramebuffers()
    {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for(size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            VkImageView attachments[] = {
                swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
				Core::log::report(FATAL_ERROR, "Vulkan : Failed to create framebuffer");
        }
    }
}
