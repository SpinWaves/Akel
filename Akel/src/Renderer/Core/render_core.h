// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 04/07/2022

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Core/core.h>
#include "Memory/allocator_GPU.h"

#include "vk_queues.h"
#include "vk_device.h"
#include "vk_surface.h"
#include "vk_instance.h"
#include "vk_semaphore.h"
#include "vk_validation_layers.h"

#include <Renderer/Command/vk_cmd_pool.h>
#include <Renderer/Command/vk_cmd_buffer.h>
#include <Renderer/SwapChain/vk_swapchain.h>
#include <Renderer/SwapChain/vk_render_pass.h>
#include <Renderer/Pipeline/vk_graphic_pipeline.h>
#include <Renderer/Descriptors/vk_descriptor_pool.h>
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

    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

    constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

    /**
     * Render_Core is a singleton that is not meant to be created anywhere
     */
    class Render_Core : public SelfInstance<Render_Core>
    {
        public:
            Render_Core();

            void init();
            void destroy();

            bool beginFrame();
            void endFrame();

            inline class WindowComponent* getWindow() noexcept { return _window; }
            inline void setWindow(class WindowComponent* window) noexcept { _window = window; }

            inline Instance&  getInstance()    { return _instance; }
            inline Device&    getDevice()      { return _device; }
            inline Surface&   getSurface()     { return _surface; }
            inline Queues&    getQueue()       { return _queues; }
            inline CmdPool&   getCmdPool()     { return _cmd_pool; }
            inline SwapChain& getSwapChain()   { return _swapchain; }
            inline Semaphore& getSemaphore()   { return _semaphore; }
            inline RenderPass& getRenderPass() { return _pass; }
            inline ValidationLayers& getLayers()   { return _layers; }
            inline DescriptorPool& getDescPool()   { return _desc_pool; }
            inline VkClearValue& getClearValue()   { return _clearColor; }
            inline CmdBuffer& getCmdBuffer(int i)  { return *_cmd_buffers[i]; }
            inline CmdBuffer& getActiveCmdBuffer() { return *_cmd_buffers[_active_image_index]; }
            inline uint32_t getActiveImageIndex()  { return _active_image_index; }
            inline uint32_t getImageIndex()        { return _image_index; }

            inline GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags) { return _allocator.allocChunk(requirements, flags); }
            inline void freeChunk(GPU_Mem_Chunk& chunk) { _allocator.freeChunk(chunk); }

            inline constexpr void requireFrameBufferResize() noexcept { _framebufferResized = true; }
            inline bool isFrameBufferResizeRequested() const noexcept { return _framebufferResized; }

        private:
            Device _device;
            Queues _queues;
            Surface _surface;
            RenderPass _pass;
            CmdPool _cmd_pool;
            Instance _instance;
            SwapChain _swapchain;
            Semaphore _semaphore;
            Allocator_GPU _allocator;
            ValidationLayers _layers;
            DescriptorPool _desc_pool;
            std::vector<CmdBuffer*> _cmd_buffers;
            VkClearValue _clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

            class WindowComponent* _window = nullptr;
            bool _framebufferResized = false;

            uint32_t _active_image_index = 0;
            uint32_t _image_index = 0;
            bool _is_init = false;
    };
}

#endif // __AK_RENDER_CORE__
