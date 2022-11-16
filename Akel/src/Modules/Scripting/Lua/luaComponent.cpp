// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 16/11/2022

#include <Modules/Scripting/Lua/luaComponent.h>
#include <Modules/Scripting/Lua/luaManager.h>
#include <Platform/input.h>
#include <Core/core.h>

namespace Ak::lua
{
	LuaComponent::LuaComponent() : Component("__lua_component")
	{
		LuaManager::get();
	}

	void LuaComponent::onAttach()
	{
	}

	void LuaComponent::update()
	{
	}

	void LuaComponent::onEvent(Input& in)
	{
		_guard = _script();
		if(_guard.valid())
			std::cout << "pouic" << std::endl;
		else
			std::cout << "babichette" << std::endl;
		in.finish();
	}

	void LuaComponent::onRender()
	{
	}

	void LuaComponent::onQuit()
	{
	}

	void LuaComponent::attach_script(std::filesystem::path path)
	{
		if(!std::filesystem::exists(path))
			Core::log::report(ERROR, "Lua Component : invalid script path, %s", path.string().c_str());
		std::cout << "before" << std::endl;
		_script = LuaManager::get().getState().load_file(path.string());
		std::cout << "attached" << std::endl;
	}
}
