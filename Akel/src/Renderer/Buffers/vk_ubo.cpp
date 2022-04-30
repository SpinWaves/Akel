// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 30/04/2022

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
