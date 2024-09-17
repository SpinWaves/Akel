// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include <Core/Core.h>
#include <Core/PreCompiled.h>

namespace Ak
{
	class JamAllocator;
	class FixedAllocator;

	namespace Core::Memory::Internal
	{
		struct AK_CORE_API ControlUnit
		{
			std::vector<std::pair<JamAllocator*, bool>> jam_stack;
			std::vector<std::pair<FixedAllocator*, bool>> fixed_stack;
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
