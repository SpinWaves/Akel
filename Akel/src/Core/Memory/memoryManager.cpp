// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/07/2021
// Updated : 08/09/2023

#include <Utils/utils.h>
#include <Core/projectFile.h>
#include <Core/core.h>
#include <Core/Event/event.h>

namespace Ak::memory::internal
{
	struct ControlUnit
	{
		std::vector<std::weak_ptr<JamAllocator>> jamStack;
		std::vector<std::weak_ptr<FixedAllocator>> fixedStack;
	};

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

	std::shared_ptr<ControlUnit> getControlUnit()
	{
		return control_unit;
	}

	void* alloc(size_t size, bool is_class)
	{
		if(is_init)
		{
			if(getMainAppProjectFile().archive()["memory_manager_enable_fixed_allocator"])
			{
				if(!is_class)
				{
					if(size <= FIXED_SIZE_1)
						return fixed1.alloc<char>(std::forward<Args>(args)...);
					else if(size <= FIXED_SIZE_2)
						return fixed2.alloc<char>(std::forward<Args>(args)...);
					else if(size <= FIXED_SIZE_3)
						return fixed3.alloc<char>(std::forward<Args>(args)...);
				}
			}
			return jam.alloc<char>(std::forward<Args>(args)...);
		}
		Core::log::report(ERROR, "Memory manager : cannot allocate pointer");
		return nullptr;
	}

	void dealloc(void* ptr)
	{
		if(getMainAppProjectFile().archive()["memory_manager_enable_fixed_allocator"])
		{
			if(fixed1.contains(ptr))
			{
				fixed1.free(ptr);
				return;
			}
			if(fixed2.contains(ptr))
			{
				fixed2.free(ptr);
				return;
			}
			if(fixed3.contains(ptr))
			{
				fixed3.free(ptr);
				return;
			}
		}
		if(jam.contains(ptr))
		{
			__jam.free(ptr);
			return;
		}
		for(auto& elem : control_unit->jamStack)
		{
			if(!elem.expired())
			{
				if(elem.lock()->contains(ptr))
				{
					elem.lock()->free(ptr);
					return;
				}
			}
		}
		for(auto& elem : control_unit->fixedStack)
		{
			if(!elem.expired())
			{
				if(elem.lock()->contains(ptr))
				{
					elem.lock()->free(ptr);
					return;
				}
			}
		}
		Core::log::report(STRONG_WARNING, "Memory manager : cannot find memory allocator for a pointer '%p'", ptr);
	}

	void fatalErrorEventHandle()
	{
		if(!is_init || !control_unit)
		{
			Core::log::report(ERROR, "Memory manager : cannot free all instanciated allocators, memory manager is not init or has been shutdown");
			return;
		}

		Core::log::report(MESSAGE, "Memory manager : trying to free all instanciated allocators...");
		int allocators_leaks = 0;
		for(auto& elem : control_unit->jamStack)
		{
			if(!elem.expired())
			{
				elem.lock()->destroy();
				if(elem.lock()->isInit())
					allocators_leaks++;
			}
		}
		for(auto& elem : control_unit->fixedStack)
		{
			if(!elem.expired())
			{
				elem.lock()->destroy();
				if(elem.lock()->is_init())
					allocators_leaks++;
			}
		}
		if(allocators_leaks != 0)
			Core::log::report(MESSAGE, "Memory manager : number of allacators not destroyed '%d'", allocators_leaks);
		else
			Core::log::report(MESSAGE, "Memory manager : all allocators have been correctly freed, program failed successfully");
	}

	void init()
	{
		std::lock_guard<std::mutex> watchdog(mutex);
		if(is_init)
			return;
		control_unit = std::make_shared<ControlUnit>();

		func::function<void(const BaseEvent&)> functor = [=](const BaseEvent& event)
		{
			if(event.what() == 167)
				fatalErrorEventHandle();
		};
		EventBus::registerListener({ functor, "__internal_memory_manager" });

		if(getMainAppProjectFile().archive()["memory_manager_enable_fixed_allocator"])
		{
			fixed1.init(FIXED_SIZE_1, 1000);
			fixed2.init(FIXED_SIZE_2, 2000);
			fixed3.init(FIXED_SIZE_3, 4000);

			fixed1.autoResize(true);
			fixed2.autoResize(true);
			fixed3.autoResize(true);
		}
		jam.init(4096 * 4096);
		jam.autoIncreaseSize(true);
		is_init = true;
	}

	void MemoryManager::end()
	{
		std::lock_guard<std::mutex> watchdog(mutex);
		if(!is_init)
			return;
		if(getMainAppProjectFile().archive()["memory_manager_enable_fixed_allocator"])
		{
			fixed1.destroy();
			fixed2.destroy();
			fixed3.destroy();
		}
		jam.destroy();
		control_unit.reset();
		is_init = false;
	}
}
