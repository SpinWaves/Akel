// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 21/12/2022

#ifndef __AK_VK_UBO__
#define __AK_VK_UBO__

#include "vk_buffer.h"

namespace Ak
{
	class UBO
	{
		public:
			void create(class RendererComponent* renderer, uint32_t size);

			void setData(uint32_t size, const void* data);
			void setDynamicData(uint32_t size, const void* data);

			void destroy() noexcept;

			unsigned int getSize() noexcept;
			unsigned int getOffset() noexcept;
			VkDeviceMemory getDeviceMemory() noexcept;
			VkBuffer& operator()() noexcept;
			VkBuffer& get() noexcept;

			inline unsigned int getSize(int i) noexcept { return _buffers[i].getSize(); }
			inline unsigned int getOffset(int i) noexcept { return _buffers[i].getOffset(); }
			inline VkDeviceMemory getDeviceMemory(int i) noexcept { return _buffers[i].getDeviceMemory(); }
			inline VkBuffer& operator()(int i) noexcept { return _buffers[i].get(); }
			inline VkBuffer& get(int i) noexcept { return _buffers[i].get(); }
		
		private:
			std::array<Buffer, MAX_FRAMES_IN_FLIGHT> _buffers;
			std::array<void*, MAX_FRAMES_IN_FLIGHT> _maps;
			class RendererComponent* _renderer = nullptr;
	};
}

#endif // __AK_VK_UBO__
