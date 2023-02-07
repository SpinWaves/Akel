// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 27/01/2023

#include <Renderer/Buffers/vk_ibo.h>

namespace Ak
{
	void IBO::setData(uint32_t size, const uint32_t* data)
	{
		if(size > _mem_chunck.size)
			Core::log::report(ERROR, "Vulkan : trying to store to much data in an index buffer (%d on %d)", size, _mem_chunck.size);
		
		if(data == nullptr)
			Core::log::report(WARNING, "Vulkan : mapping null data in an index buffer");

		void* temp = nullptr;
		mapMem(&temp);
			std::memcpy(temp, data, static_cast<size_t>(size));
		unmapMem();
	}
}
