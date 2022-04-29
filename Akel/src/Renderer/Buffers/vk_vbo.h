// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 29/04/2022

#ifndef __AK_VK_VBO__
#define __AK_VK_VBO__

#include "vk_buffer.h"

namespace Ak
{
	class VBO : public Buffer
	{
		public:
			inline void create(uint32_t size) { Buffer::create(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT); }

			void setData(uint32_t size, const void* data);
			void setSubData(uint32_t offset, uint32_t size, const void* data);

			inline void bind() noexcept
			{
				VkDeviceSize offsets[1] = { 0 };
				vkCmdBindVertexBuffers(Render_Core::get().getActiveCmdBuffer().get(), 0, 1, &_buffer, offsets);
			}

		private:
			uint32_t _used_size = 0;
	};
}

#endif // __AK_VK_VBO__
