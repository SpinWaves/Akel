// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/Memory/JamAllocator.h>
#include <Core/Memory/FixedAllocator.h>
#include <Core/Logs.h>
#include <Core/PreCompiled.h>
#include <Core/Memory/MemoryManager.h>
#include <Core/EventListener.h>
#include <Core/EventBase.h>
#include <Core/EventBus.h>

namespace Ak::Core::Memory::Internal
{
	static JamAllocator jam;
	static FixedAllocator fixed1;
	static FixedAllocator fixed2;
	static FixedAllocator fixed3;
	static std::mutex mutex;
	std::shared_ptr<ControlUnit> control_unit;
	static bool is_init = false;

	constexpr const int FIXED_SIZE_1 = 16;
	constexpr const int FIXED_SIZE_2 = 32;
	constexpr const int FIXED_SIZE_3 = 96;

	std::shared_ptr<ControlUnit> GetControlUnit()
	{
		return control_unit;
	}

	void FatalErrorEventHandle()
	{
		if(!is_init || !control_unit)
		{
			Error("Memory manager : cannot free all instanciated allocators, memory manager is not init or has been shutdown");
			return;
		}

		Message("Memory manager : trying to free all instanciated allocators...");
		int allocators_leaks = 0;
		for(auto& elem : control_unit->jam_stack)
		{
			if(!elem.second)
				continue;
			elem.first->Destroy();
			if(elem.first->IsInit())
				allocators_leaks++;
		}
		for(auto& elem : control_unit->fixed_stack)
		{
			if(!elem.second)
				continue;
			elem.first->Destroy();
			if(elem.first->IsInit())
				allocators_leaks++;
		}
		if(allocators_leaks != 0)
			Message("Memory manager : number of allacators not destroyed '%'", allocators_leaks);
		else
			Message("Memory manager : all allocators have been correctly freed, program failed successfully");
		std::exit(0); // ugly, mem manager should not have power to exit the program
	}

	void Init()
	{
		std::lock_guard<std::mutex> watchdog(mutex);
		if(is_init)
			return;
		control_unit = std::make_shared<ControlUnit>();

		func::function<void(const EventBase&)> functor = [=](const EventBase& event)
		{
			if(event.What() == 167)
				FatalErrorEventHandle();
		};
		EventBus::RegisterListener({ functor, "__internal_memory_manager" });

		{
			fixed1.Init(FIXED_SIZE_1, 1000);
			fixed2.Init(FIXED_SIZE_2, 2000);
			fixed3.Init(FIXED_SIZE_3, 4000);

			fixed1.AutoResize(true);
			fixed2.AutoResize(true);
			fixed3.AutoResize(true);
		}
		jam.Init(4096 * 4096);
		jam.AutoIncreaseSize(true);
		is_init = true;
	}

	void* Alloc(std::size_t size, bool is_class)
	{
		if(!is_init)
			Init();
		{
			if(!is_class)
			{
				if(size <= FIXED_SIZE_1)
					return fixed1.AllocSize<void>(size);
				else if(size <= FIXED_SIZE_2)
					return fixed2.AllocSize<void>(size);
				else if(size <= FIXED_SIZE_3)
					return fixed3.AllocSize<void>(size);
			}
		}
		return jam.AllocSize<void>(size);
	}

	void Dealloc(void* ptr)
	{
		if(ptr == nullptr)
			return;
		{
			if(fixed1.Contains(ptr))
			{
				fixed1.Free(ptr);
				return;
			}
			if(fixed2.Contains(ptr))
			{
				fixed2.Free(ptr);
				return;
			}
			if(fixed3.Contains(ptr))
			{
				fixed3.Free(ptr);
				return;
			}
		}
		if(jam.Contains(ptr))
		{
			jam.Free(ptr);
			return;
		}
		for(auto& elem : control_unit->jam_stack)
		{
			if(!elem.second)
				continue;
			if(elem.first->Contains(ptr))
			{
				elem.first->Free(ptr);
				return;
			}
		}
		for(auto& elem : control_unit->fixed_stack)
		{
			if(!elem.second)
				continue;
			if(elem.first->Contains(ptr))
			{
				elem.first->Free(ptr);
				return;
			}
		}
		Warning("Memory manager : cannot find memory allocator for a pointer '%'", ptr);
	}

	void Shutdown()
	{
		std::lock_guard<std::mutex> watchdog(mutex);
		if(!is_init)
			return;
		{
			fixed1.Destroy();
			fixed2.Destroy();
			fixed3.Destroy();
		}
		jam.Destroy();
		control_unit.reset();
		is_init = false;
	}
}
