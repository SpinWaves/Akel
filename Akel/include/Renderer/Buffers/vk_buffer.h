// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 19/11/2023

#ifndef __AK_VK_BUFFER__
#define __AK_VK_BUFFER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Core/memory.h>

namespace Ak
{
	class Buffer
	{
		public:
			enum class kind { constant, dynamic, uniform };

			void create(kind type, VkDeviceSize size, VkBufferUsageFlags usage, const void* data = nullptr);
			void destroy() noexcept;

			inline void mapMem(void** data) noexcept { Render_Core::get().getAllocator().mapMemory(_allocation, data); _is_mapped = true; }
			inline bool isMapped() const noexcept { return _is_mapped; }
			inline void unmapMem() noexcept { Render_Core::get().getAllocator().unmapMemory(_allocation); _is_mapped = false; }

			void flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

			inline VkBuffer operator()() const noexcept { return _buffer; }
			inline VkBuffer get() const noexcept { return _buffer; }
			inline VkDeviceSize getSize() const noexcept { return _size; }
			inline VkDeviceSize getOffset() const noexcept { return _offset; }

			void swap(Buffer& buffer);

		protected:
			VmaAllocation _allocation;
			VkBuffer _buffer = VK_NULL_HANDLE;
			VkDeviceSize _offset = 0;
			VkDeviceSize _size = 0;

		private:
			void createBuffer(VkBufferUsageFlags usage, VmaAllocationCreateInfo info, VkDeviceSize size);
			void pushToGPU() noexcept;
			VkBufferUsageFlags _usage = 0;
			VkMemoryPropertyFlags _flags = 0;
			bool _is_mapped = false;
	};
}

#endif // __AK_VK_BUFFER__
