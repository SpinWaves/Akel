// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 06/11/2023

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
			enum class kind { constant, dynamic, uniform };

			void create(kind type, VkDeviceSize size, VkBufferUsageFlags usage, const void* data = nullptr);
			void destroy() noexcept;

			inline void mapMem(void** data = nullptr, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) noexcept
			{
				if(vkMapMemory(Render_Core::get().getDevice().get(), _mem_chunck.memory, _mem_chunck.offset + offset, size, 0, data) != VK_SUCCESS)
					Core::log::report(FATAL_ERROR, "Vulkan : failed to map a buffer");
			}
			inline void unmapMem() noexcept { vkUnmapMemory(Render_Core::get().getDevice().get(), _mem_chunck.memory); }

			void flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

			inline unsigned int getSize() const noexcept { return _mem_chunck.size; }
			inline unsigned int getOffset() const noexcept { return _mem_chunck.offset; }
			inline VkDeviceMemory getDeviceMemory() const noexcept { return _mem_chunck.memory; }
			inline const VkBuffer& operator()() const noexcept { return _buffer; }
			inline const VkBuffer& get() const noexcept { return _buffer; }

			void swap(Buffer& buffer);

		protected:
			GPU_Mem_Chunk _mem_chunck;
			VkBuffer _buffer = VK_NULL_HANDLE;

		private:
			void createBuffer(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void pushToGPU() noexcept;

			VkBufferUsageFlags _usage = 0;
			VkMemoryPropertyFlags _flags = 0;
	};
}

#endif // __AK_VK_BUFFER__
