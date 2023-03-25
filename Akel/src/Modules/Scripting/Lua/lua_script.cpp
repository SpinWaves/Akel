// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/03/2023
// Updated : 25/03/2023

#include <Modules/Scripting/Lua/lua_script.h>
#include <Core/log.h>

namespace Ak
{
	static int32_t id_counter = 0;
	extern Entity* __entity;

	LuaScript::LuaScript() : Script(), _id(id_counter++) {}

	void LuaScript::runOnInit(Entity* entity)
	{
		if(!_on_init.valid())
			return;
		__entity = entity;
		sol::protected_function_result result = _on_init();
		if(!result.valid())
		{
			sol::error err = result;
			Core::log::report(ERROR, "Lua Script : failed to execute init function : %s", err.what());
		}
	}

	void LuaScript::runOnUpdate(Entity* entity, float delta)
	{
		__entity = entity;
		if(!_on_update.valid())
			return;
		sol::protected_function_result result = _on_update(delta);
		if(!result.valid())
		{
			sol::error err = result;
			Core::log::report(ERROR, "Lua Script : failed to execute update function : %s", err.what());
		}
	}

	void LuaScript::runOnQuit(Entity* entity)
	{
		__entity = entity;
		if(!_on_quit.valid())
			return;
		sol::protected_function_result result = _on_quit();
		if(!result.valid())
		{
			sol::error err = result;
			Core::log::report(ERROR, "Lua Script : failed to execute quit function : %s", err.what());
		}
	}
}
