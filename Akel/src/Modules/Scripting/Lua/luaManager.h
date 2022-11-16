// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/11/2022
// Updated : 16/11/2022

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
			LuaManager();

			inline sol::state& getState() { _state; }
			void bindLogs();
			void bindInputs(Input& in);

			~LuaManager() = default;

		private:
			sol::state _state;
	};
}

#endif
