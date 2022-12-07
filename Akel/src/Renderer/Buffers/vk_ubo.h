// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 07/12/2022

#ifndef __AK_VK_UBO__
#define __AK_VK_UBO__

#include "vk_buffer.h"

namespace Ak
{
	class UBO : public Buffer
	{
		public:
			inline void create(uint32_t size) { Buffer::create(Buffer::kind::uniform, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT); }

			void setData(uint32_t size, const void* data);
			void setDynamicData(uint32_t size, const void* data);
	};
}

#endif // __AK_VK_UBO__
