// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 16/11/2022

#include <Modules/Scripting/Lua/luaManager.h>
#include <Core/core.h>

#define SOL_ALL_SAFETIES_ON 1

namespace Ak::lua
{
	LuaManager::LuaManager() : _state()
	{
		_state.open_libraries(sol::lib::base, sol::lib::io, sol::lib::package, sol::lib::math, sol::lib::table);
	//	LuaManager::get().bindLogs();
	}

	void LuaManager::bindLogs()
	{
		auto log = _state["Ak"].get_or_create<sol::table>();

		log.set_function("message", [](std::string message)
				{ Core::log::report(MESSAGE, std::move(message)); });
		log.set_function("warning", [](std::string message)
				{ Core::log::report(WARNING, std::move(message)); });
		log.set_function("strong_warning", [](std::string message)
				{ Core::log::report(STRONG_WARNING, std::move(message)); });
		log.set_function("error", [](std::string message)
				{ Core::log::report(ERROR, std::move(message)); });
		log.set_function("fatal_error", [](std::string message)
				{ Core::log::report(FATAL_ERROR, std::move(message)); });
	}

	void LuaManager::bindInputs(Input& in)
	{
		auto input = _state["Ak_input"].get_or_create<sol::table>();

		input.set_function("getInKey", [&](SDL_Scancode key, action kind) -> bool
				{ return in.getInKey(key, kind); });
		input.set_function("getInMouse", [&](uint8_t key, action kind) -> bool
				{ return in.getInMouse(key, kind); });
		input.set_function("isMouseMoving", [&]() -> bool
				{ return in.isMouseMoving(); });

		input.set_function("getX", [&]() -> int
				{ return in.getX(); });
		input.set_function("getY", [&]() -> int
				{ return in.getY(); });
		input.set_function("getXRel", [&]() -> int
				{ return in.getXRel(); });
		input.set_function("getYRel", [&]() -> int
				{ return in.getYRel(); });

		input.set_function("finish", [&]() -> void
				{ return in.finish(); });
		input.set_function("run", [&]() -> void
				{ return in.run(); });

		std::initializer_list<std::pair<sol::string_view, SDL_Scancode>> keyItems = {
			{ "AK_KEY_A", AK_KEY_A },
			{ "AK_KEY_B", AK_KEY_B },
			{ "AK_KEY_C", AK_KEY_C },
			{ "AK_KEY_D", AK_KEY_D },
			{ "AK_KEY_E", AK_KEY_E },
			{ "AK_KEY_F", AK_KEY_F },
			{ "AK_KEY_G", AK_KEY_G },
			{ "AK_KEY_H", AK_KEY_H },
			{ "AK_KEY_I", AK_KEY_I },
			{ "AK_KEY_J", AK_KEY_J },
			{ "AK_KEY_K", AK_KEY_K },
			{ "AK_KEY_L", AK_KEY_L },
			{ "AK_KEY_M", AK_KEY_M },
			{ "AK_KEY_N", AK_KEY_N },
			{ "AK_KEY_O", AK_KEY_O },
			{ "AK_KEY_P", AK_KEY_P },
			{ "AK_KEY_Q", AK_KEY_Q },
			{ "AK_KEY_R", AK_KEY_R },
			{ "AK_KEY_S", AK_KEY_S },
			{ "AK_KEY_T", AK_KEY_T },
			{ "AK_KEY_U", AK_KEY_U },
			{ "AK_KEY_V", AK_KEY_V },
			{ "AK_KEY_W", AK_KEY_W },
			{ "AK_KEY_X", AK_KEY_X },
			{ "AK_KEY_Y", AK_KEY_Y },
			{ "AK_KEY_Z", AK_KEY_Z },

			{ "AK_KEY_0", AK_KEY_0 },
			{ "AK_KEY_1", AK_KEY_1 },
			{ "AK_KEY_2", AK_KEY_2 },
			{ "AK_KEY_3", AK_KEY_3 },
			{ "AK_KEY_4", AK_KEY_4 },
			{ "AK_KEY_5", AK_KEY_5 },
			{ "AK_KEY_6", AK_KEY_6 },
			{ "AK_KEY_7", AK_KEY_7 },
			{ "AK_KEY_8", AK_KEY_8 },
			{ "AK_KEY_9", AK_KEY_9 },
        };
        _state.new_enum<SDL_Scancode, false>("Ak_key", keyItems);
	}
}