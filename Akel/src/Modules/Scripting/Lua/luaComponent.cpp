// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 15/11/2022

#include <Modules/Scripting/Lua/luaComponent.h>
#include <Platform/input.h>
#include <Core/core.h>

#define SOL_ALL_SAFETIES_ON 1

namespace Ak::lua
{
	LuaComponent::LuaComponent() : Component("__lua_component") {}

	void LuaComponent::onAttach()
	{
		_state = Ak::create_shared_ptr_w<sol::state>();
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
		_state.reset();
	}
}
