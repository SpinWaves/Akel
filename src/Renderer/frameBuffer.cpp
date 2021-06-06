// This file is a part of AtlasEngine
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#include <Renderer/renderer.h>

namespace AE
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
                std::cout << "failed to create framebuffer!" << std::endl;
        }
    }
}

