// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/11/2022
// Updated : 14/01/2023

#ifndef __AK_LUA_MANAGER__
#define __AK_LUA_MANAGER__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Platform/input.h>

namespace Ak::lua
{
	class LuaManager : public SelfInstance<LuaManager>
	{
		public:
			LuaManager() = default;

			void init();
			inline sol::state& getState() { _state; }
			void bindLogs();
			void bindInputs(Input& in);

			~LuaManager() = default;

		private:
			sol::state _state;
	};
}

#endif
