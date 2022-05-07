// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 07/05/2022

#include "vk_ubo.h"

namespace Ak
{
	void UBO::setData(uint32_t size, const void* data)
	{
		void* temp = nullptr;
		mapMem(temp);
			std::memcpy(temp, data, static_cast<size_t>(size));
		unmapMem();
	}

	void UBO::setDynamicData(uint32_t size, uint32_t typeSize, const void* data)
	{
		void* temp = nullptr;
		mapMem(temp);
			std::memcpy(temp, data, static_cast<size_t>(size));
			Buffer::flush();
		unmapMem();
	}
}
