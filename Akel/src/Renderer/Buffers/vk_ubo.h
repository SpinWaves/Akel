// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 09/05/2022

#ifndef __AK_VK_UBO__
#define __AK_VK_UBO__

#include "vk_buffer.h"

namespace Ak
{
	class UBO : public Buffer
	{
		public:
			inline void create(uint32_t size) { Buffer::create(Buffer::kind::dynamic, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT); }

			void setData(uint32_t size, const void* data);
			void setDynamicData(uint32_t size, uint32_t typeSize, const void* data);
	};
}

#endif // __AK_VK_UBO__
