// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/11/2023
// Updated : 15/11/2023

#ifndef __AK_VK_MEMORY__
#define __AK_VK_MEMORY__

#include <Akpch.h>

namespace Ak
{
	class GPUallocator
	{
		public:
			GPUallocator() = default;

			void init() noexcept;
			void destroy() noexcept;

			VmaAllocation createBuffer(const VkBufferCreateInfo* binfo, const VmaAllocationCreateInfo* vinfo, VkBuffer& buffer, const char* name = nullptr) noexcept;
			void destroyBuffer(VmaAllocation allocation, VkBuffer buffer) noexcept;

			VmaAllocation createImage(const VkImageCreateInfo* iminfo, const VmaAllocationCreateInfo* vinfo, VkImage& image, const char* name = nullptr) noexcept;
			void destroyImage(VmaAllocation allocation, VkImage image) noexcept;

			void mapMemory(VmaAllocation allocation, void** data) noexcept;
			void unmapMemory(VmaAllocation allocation) noexcept;

			void dumpMemoryToJson();

			void flush(VmaAllocation allocation, VkDeviceSize size, VkDeviceSize offset) noexcept;

			~GPUallocator() = default;

		private:
			VmaAllocator _allocator;
	};
}

#endif
