// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/11/2022
// Updated : 15/11/2022

#ifndef __AK_LUA_MANAGER__
#define __AK_LUA_MANAGER__

#include <Akpch.h>
#include <Utils/selfInstance.h>

namespace Ak
{
	class LuaManager : public SelfInstance<LuaManager>
	{
		public:
			inline std::shared_ptr<sol::state> getState() { _state; }

		private:
			LuaManager() = default;
			~LuaManager() = default;

			std::shared_ptr<sol::state> _state;
	};
}

#endif
