// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 10/04/2022

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Core/core.h>
#include "Memory/memory_GPU.h"

#include "vk_queues.h"
#include "vk_device.h"
#include "vk_surface.h"
#include "vk_instance.h"
#include "vk_validation_layers.h"
#include <Renderer/SwapChain/vk_swapchain.h>

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
            Render_Core();

            void init(WindowComponent* window);

            inline WindowComponent* getWindow() const noexcept { return _window; }
            inline void setWindow(WindowComponent* window) noexcept { _window = window; }

            inline const Instance&  getInstance()  const { return _instance; }
            inline const Device&    getDevice()    const { return _device; }
            inline const Surface&   getSurface()   const { return _surface; }
            inline const Queues&    getQueue()     const { return _queues; }
            inline const SwapChain& getSwapChain() const { return _swapchain; }
            inline const ValidationLayers& getLayers() const { return _layers; }

            inline GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags) { return _allocator.allocChunk(requirements, flags); }

            inline constexpr void requireFrameBufferResize() noexcept { _framebufferResized = true; }

        private:
            Device _device;
            Queues _queues;
            Surface _surface;
            Instance _instance;
            SwapChain _swapchain;
            Allocator_GPU _allocator;
            ValidationLayers _layers;

            WindowComponent* _window = nullptr;
            bool _framebufferResized = false;
    };
}

#endif // __AK_RENDER_CORE__
