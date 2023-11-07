// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 06/11/2023

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

			unsigned int getSize() const noexcept;
			unsigned int getOffset() const noexcept;
			VkDeviceMemory getDeviceMemory() const noexcept;
			const VkBuffer& operator()() const noexcept;
			const VkBuffer& get() const noexcept;

			inline unsigned int getSize(int i) const noexcept { return _buffers[i].getSize(); }
			inline unsigned int getOffset(int i) const noexcept { return _buffers[i].getOffset(); }
			inline VkDeviceMemory getDeviceMemory(int i) const noexcept { return _buffers[i].getDeviceMemory(); }
			inline const VkBuffer& operator()(int i) const noexcept { return _buffers[i].get(); }
			inline const VkBuffer& get(int i) const noexcept { return _buffers[i].get(); }
		
		private:
			std::array<Buffer, MAX_FRAMES_IN_FLIGHT> _buffers;
			std::array<void*, MAX_FRAMES_IN_FLIGHT> _maps;
			class RendererComponent* _renderer = nullptr;
	};
}

#endif // __AK_VK_UBO__
