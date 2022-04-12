// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 12/04/2022

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Core/core.h>
#include "Memory/memory_GPU.h"

#include "vk_queues.h"
#include "vk_device.h"
#include "vk_surface.h"
#include "vk_instance.h"
#include "vk_semaphore.h"
#include "vk_validation_layers.h"
#include <Renderer/Command/vk_cmd_pool.h>
#include <Renderer/Command/vk_cmd_buffer.h>
#include <Renderer/SwapChain/vk_swapchain.h>
#include <Renderer/Pipeline/vk_graphic_pipeline.h>
//#include <Renderer/Pipeline/vk_compute_pipeline.h>

namespace Ak
{
    namespace RCore
    {
        void checkVk(VkResult result);
    }

    #ifdef AK_DEBUG
        constexpr const bool enableValidationLayers = true;
    #else
        constexpr const bool enableValidationLayers = false;
    #endif

    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    
    constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

    class WindowComponent;

    /**
     * Render_Core is a singleton that is not meant to be created anywhere
     */
    class Render_Core : public SelfInstance<Render_Core>
    {
        public:
            Render_Core() = default;
            void init();
            void destroy();

            void init(WindowComponent* window);

            inline WindowComponent* getWindow() const noexcept { return _window; }
            inline void setWindow(WindowComponent* window) noexcept { _window = window; }

            inline Instance&  getInstance()  const { return _instance; }
            inline Device&    getDevice()    const { return _device; }
            inline Surface&   getSurface()   const { return _surface; }
            inline Queues&    getQueue()     const { return _queues; }
            inline CmdPool&   getCmdPool()   const { return _cmd_pool; }
            inline SwapChain& getSwapChain() const { return _swapchain; }
            inline ValidationLayers& getLayers()   const { return _layers; }
            inline VkClearValue& getClearValue()   const { return _clearColor; }
            inline CmdPool&   getCmdBuffer(int i)  const { return _cmd_buffers[i]; }
            inline CmdBuffer& getActiveCmdBuffer() const { return _cmd_buffers[_active_image_index]; }
            inline uint32_t getActiveImageIndex()  const { return _active_image_index; }

            inline GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags) { return _allocator.allocChunk(requirements, flags); }
            inline void freeChunck(GPU_Mem_Chunk chunck) { _allocator.freeChunck(chunck); }

            inline constexpr void requireFrameBufferResize() noexcept { _framebufferResized = true; }

        private:
            Device _device;
            Queues _queues;
            Surface _surface;
            CmdPool _cmd_pool;
            Instance _instance;
            SwapChain _swapchain;
            Allocator_GPU _allocator;
            ValidationLayers _layers;
            std::vector<CmdBuffer> _cmd_buffers;
            VkClearValue _clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

            WindowComponent* _window = nullptr;
            bool _framebufferResized = false;

            uint32_t _active_image_index = 0;
    };
}

#endif // __AK_RENDER_CORE__
