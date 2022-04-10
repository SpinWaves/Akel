// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 10/04/2022

#ifndef __AK_VK_BUFFER__
#define __AK_VK_BUFFER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Core/Memory/chunck.h>

namespace Ak
{
	class Buffer
	{
		public:
			void create(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags const void* data = nullptr);
			inline void destroy() noexcept
			{
				static_assert(_buffer != VK_NULL_HANDLE, "trying to destroy an uninit video buffer");
				vkDestroyBuffer(Render_Core::get().getDevice().get(), _buffer, nullptr);
			}

			void storeInGPU() noexcept;
			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

			inline void mapMemory(void** data = nullptr) noexcept
			{
				if(vkMapMemory(Render_Core::get().getDevice().get(), _buffer, 0, _mem_chunck.size, 0, *data) != VK_SUCCESS)
					Core::log::report(FATAL_ERROR, "Vulkan : failed to map a buffer");
			}
			inline void unmapMemory() noexcept { vkUnmapMemory(Render_Core::get().getDevice().get(), _buffer); }

			inline unsigned int getSize() const noexcept { return _mem_chunck.size; }
			inline VkDeviceMemory getDeviceMemory() const noexcept { return _mem_chunck.memory; }
			inline VkBuffer& operator()() const noexcept { return _buffer; }
			inline VkBuffer& get() const noexcept { return _buffer; }

		private:
			GPU_Mem_Chunk _mem_chunck;
			VkBuffer _buffer = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_BUFFER__
