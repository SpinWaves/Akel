// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 08/12/2022

#ifndef __AK_VK_UBO__
#define __AK_VK_UBO__

#include "vk_buffer.h"

namespace Ak
{
	class UBO : public Buffer
	{
		public:
			void create(uint32_t size);

			void setData(uint32_t size, const void* data);
			void setDynamicData(uint32_t size, const void* data);
		
		private:
			void* _map = nullptr;
	};
}

#endif // __AK_VK_UBO__
