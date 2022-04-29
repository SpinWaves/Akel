// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 29/04/2022

#ifndef __AK_VK_iBO__
#define __AK_VK_iBO__

#include "vk_buffer.h"

namespace Ak
{
	class IBO : public Buffer
	{
		public:
			inline void create(uint32_t size) { Buffer::create(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); }

			void setData(uint32_t size, const void* data);

			void bind();
	};
}

#endif // __AK_VK_IBO__
