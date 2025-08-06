// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_MEMORY_DEVICE_ALLOCATOR_H
#define AK_VULKAN_MEMORY_DEVICE_ALLOCATOR_H

#include <Drivers/Vulkan/Memory/Block.h>
#include <Drivers/Vulkan/Memory/Chunk.h>

namespace Ak
{
	constexpr std::size_t SMALL_HEAP_MAX_SIZE = (1024ULL * 1024 * 1024); // 1GB
	constexpr std::size_t DEFAULT_LARGE_HEAP_BLOCK_SIZE = (256ULL * 1024 * 1024); // 256MiB
	constexpr std::uint32_t NEW_BLOCK_SIZE_SHIFT_MAX = 3;

	class DeviceAllocator
	{
		public:
			DeviceAllocator(class VulkanDevice& device);

			[[nodiscard]] inline std::size_t GetAllocationsCount() const noexcept { return m_allocations_count; }

			[[nodiscard]] MemoryBlock Allocate(VkDeviceSize size, VkDeviceSize alignment, std::int32_t memory_type_index, bool dedicated_chunk = false);
			void Deallocate(const MemoryBlock& block);

			[[nodiscard]] inline std::uint32_t GetVramUsage() const noexcept { return m_vram_usage; }
			[[nodiscard]] inline std::uint32_t GetVramHostVisibleUsage() const noexcept { return m_vram_host_visible_usage; }

			[[nodiscard]] std::optional<std::uint32_t> FindMemoryType(std::uint32_t filter, VkMemoryPropertyFlags properties, bool issue_error = true) const;

			~DeviceAllocator() = default;

		private:
			VkDeviceSize CalcPreferredChunkSize(std::uint32_t mem_type_index);

		private:
			std::vector<UniquePtr<MemoryChunk>> m_chunks;
			VkPhysicalDeviceMemoryProperties m_mem_props;
			class VulkanDevice& m_device;
			std::size_t m_allocations_count = 0;
			std::mutex m_alloc_mutex;
			std::mutex m_dealloc_mutex;
			std::uint32_t m_vram_usage = 0;
			std::uint32_t m_vram_host_visible_usage = 0;
			bool m_last_chunk_creation_failed = false;
	};
}

#endif
