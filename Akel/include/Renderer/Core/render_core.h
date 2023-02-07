// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 27/01/2023

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Core/core.h>
#include <Core/profile.h>
#include <Utils/selfInstance.h>
#include "Memory/allocator_GPU.h"

#include "vk_queues.h"
#include "vk_device.h"
#include "vk_instance.h"
#include "vk_validation_layers.h"

namespace Ak
{
    namespace RCore
    {
        void checkVk(VkResult result);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    }

    #ifdef AK_DEBUG
        constexpr const bool enableValidationLayers = true;
    #else
        constexpr const bool enableValidationLayers = false;
    #endif

    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

    /**
     * Render_Core is a singleton that is not meant to be created anywhere by the user
     */
    class AK_API Render_Core : public SelfInstance<Render_Core>
    {
        public:
            Render_Core() = default;

            void init();
            void destroy();

			inline bool is_init() noexcept { return _is_init; }
            inline Instance&  getInstance() noexcept { return _instance; }
            inline Device&    getDevice() noexcept { return _device; }
            inline Queues&    getQueue() noexcept { return _queues; }
            inline ValidationLayers& getLayers() noexcept { return _layers; }

            inline GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags) { return _allocator.allocChunk(requirements, flags); }
            inline void freeChunk(GPU_Mem_Chunk& chunk) { _allocator.freeChunk(chunk); }
			//inline const VmaAllocator& getAllocator() const noexcept { return _allocator; }
			
			~Render_Core() = default;

        private:
            Device _device;
            Queues _queues;
            Instance _instance;
            Allocator_GPU _allocator;
			//VmaAllocator _allocator;
            ValidationLayers _layers;

            bool _is_init = false;
    };
}

#endif // __AK_RENDER_CORE__
