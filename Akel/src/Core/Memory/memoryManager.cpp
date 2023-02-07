// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/07/2021
// Updated : 15/11/2022

#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
    void MemoryManager::init()
    {
		if(_is_init)
			return;
        control_unit = std::make_shared<ControlUnit>();
		if(getMainAppProjectFile().getBoolValue("memory_manager_enable_fixed_allocator"))
		{
			__fixed1.init(16, 100);
			__fixed2.init(32, 200);
			__fixed3.init(96, 400);

			__fixed1.autoResize(true);
			__fixed2.autoResize(true);
			__fixed3.autoResize(true);
		}
		__jam.init(4096 * 4096);
		__jam.auto_increase_size(true);
		_is_init = true;
    }
    void MemoryManager::end()
    {
		if(!_is_init)
			return;
		if(getMainAppProjectFile().getBoolValue("memory_manager_enable_fixed_allocator"))
		{
			__fixed1.destroy();
			__fixed2.destroy();
			__fixed3.destroy();
		}
		__jam.destroy();
		_is_init = false;
    }
}
