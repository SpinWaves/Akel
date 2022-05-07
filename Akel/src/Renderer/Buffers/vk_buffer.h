// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_BUFFER__
#define __AK_VK_BUFFER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Core/Memory/chunk.h>

namespace Ak
{
	class Buffer
	{
		public:
			enum class kind { constant, dynamic };

			void create(kind type, VkDeviceSize size, VkBufferUsageFlags usage, const void* data = nullptr);
			inline void destroy() noexcept
			{
				static_assert(_buffer != VK_NULL_HANDLE, "trying to destroy an uninit video buffer");
				vkDestroyBuffer(Render_Core::get().getDevice().get(), _buffer, nullptr);
				Render_Core::get().freeChunck(_mem_chunck);
			}

			inline void mapMem(void* data = nullptr, VkDeviceSize size = VK_WHOLE_SIZE) noexcept
			{
				if(vkMapMemory(Render_Core::get().getDevice().get(), _buffer, _mem_chunck.offset, size, 0, data) != VK_SUCCESS)
					Core::log::report(ERROR, "Vulkan : failed to map a buffer");
			}
			inline void unmapMem() noexcept { vkUnmapMemory(Render_Core::get().getDevice().get(), _buffer); }

			void flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

			inline unsigned int getSize() noexcept { return _mem_chunck.size; }
			inline unsigned int getOffset() noexcept { return _mem_chunck.offset; }
			inline VkDeviceMemory getDeviceMemory() noexcept { return _mem_chunck.memory; }
			inline VkBuffer& operator()() noexcept { return _buffer; }
			inline VkBuffer& get() noexcept { return _buffer; }

			void swap(Buffer& buffer);

		private:
			void createBuffer(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			uint32_t findMemoryType(uint32_t typeFilter);
			void pushToGPU() noexcept;

			GPU_Mem_Chunk _mem_chunck;
			VkBuffer _buffer = VK_NULL_HANDLE;
			VkBufferUsageFlags _usage;
			VkMemoryPropertyFlags _flags;
	};
}

#endif // __AK_VK_BUFFER__
