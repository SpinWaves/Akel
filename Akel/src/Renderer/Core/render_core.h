// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 28/03/2022

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Renderer/Core/Memory/memory_GPU.h>
#include <Core/core.h>

#include "physicalDevice.h"
#include "logicalDevice.h"
#include "instance.h"
#include "surface.h"

namespace Ak
{
    namespace RCore
    {
        void checkVk(VkResult result);
    }

    /**
     * Render_Core is a singleton that is not meant to be created anywhere
     */ 
    class Render_Core : public SelfInstance<Render_Core>
    {
        public:
            const std::shared_ptr<CommandPool>& getCommandPool(const std::thread::id &threadId = std::this_thread::get_id());
            const Descriptor* getAttachment(const std::string &name) const;
            const Swapchain* getSwapchain() const { return swapchain.get(); }
            const VkPipelineCache& getPipelineCache() const { return pipelineCache; }
            const PhysicalDevice* getPhysicalDevice() const { return physicalDevice.get(); }
            const Surface* getSurface() const { return surface.get(); }
            const LogicalDevice* getLogicalDevice() const { return logicalDevice.get(); }

            constexpr void requireFrameBufferResize() noexcept { framebufferResized = true; }

        private:
            Render_Core();

            void createPipelineCache();
            void resetRenderStages();
            void recreateSwapchain();
            void recreateCommandBuffers();
            void recreatePass(RenderStage& renderStage);
            void recreateAttachmentsMap();
            bool startRenderpass(RenderStage& renderStage);
            void endRenderpass(RenderStage& renderStage);

            std::unique_ptr<Renderer> renderer;
            std::map<std::string, const Descriptor*> attachments;
            std::unique_ptr<Swapchain> swapchain;

            std::map<std::thread::id, std::shared_ptr<CommandPool>> commandPools;
            ElapsedTime elapsedPurge;

            VkPipelineCache pipelineCache = VK_NULL_HANDLE;
            std::vector<VkSemaphore> presentCompletes;
            std::vector<VkSemaphore> renderCompletes;
            std::vector<VkFence> flightFences;
            std::size_t currentFrame = 0;
            bool framebufferResized = false;

            std::vector<std::unique_ptr<CommandBuffer>> commandBuffers;

            std::unique_ptr<Instance> instance;
            std::unique_ptr<PhysicalDevice> physicalDevice;
            std::unique_ptr<Surface> surface;
            std::unique_ptr<LogicalDevice> logicalDevice;
    };
}

#endif // __AK_RENDER_CORE__
