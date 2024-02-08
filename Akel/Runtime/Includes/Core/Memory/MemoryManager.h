// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 08/02/2024

#ifndef __AK_CORE_MEMORY_MANAGER__
#define __AK_CORE_MEMORY_MANAGER__

#include <Core/Core.h>
#include <Core/PreCompiled.h>

#include <Core/Memory/JamAllocator.h>
#include <Core/Memory/FixedAllocator.h>

namespace Ak
{
	namespace Core::Memory::Internal
	{
		struct AK_CORE_API ControlUnit
		{
			std::vector<std::weak_ptr<JamAllocator>> jam_stack;
			std::vector<std::weak_ptr<FixedAllocator>> fixed_stack;
		};
		AK_CORE_API void* Alloc(std::size_t size, bool is_class);
		AK_CORE_API std::shared_ptr<ControlUnit> GetControlUnit();
		AK_CORE_API void Dealloc(void* ptr);
	}

	template<typename T, typename ... Args>
	inline T* MemAlloc(Args&& ... args);

	template<typename T = void>
	inline T* MemAllocSize(std::size_t size);

	template<typename T>
	inline void MemFree(T* ptr);
}

#include <Core/Memory/MemoryManager.inl>

#endif
