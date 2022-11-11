// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 10/11/2022

#include <Modules/Scripting/Lua/luaComponent.h>
#include <Platform/input.h>

namespace Ak::lua
{
	LuaComponent::LuaComponent() : Component("__lua_component") {}

	void LuaComponent::onAttach()
	{
		
	}

	void LuaComponent::update()
	{
		
	}

	void LuaComponent::onEvent(Input& in)
	{
		in.finish();
	}

	void LuaComponent::onRender()
	{
		
	}

	void LuaComponent::onQuit()
	{
		
	}
}
