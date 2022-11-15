// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 15/11/2022

#ifndef __AK_LUA_COMPONENT__
#define __AK_LUA_COMPONENT__

#include <Akpch.h>
#include <Core/Components/components.h>

namespace Ak::lua
{
	class LuaComponent : public Component
	{
		public:
			LuaComponent();

			void onAttach() override;
			void update() override;
			void onRender() override;
			void onEvent(Input& in) override;
			void onQuit() override;

			~LuaComponent() = default;

		private:
			std::shared_ptr<sol::state> _state;
	};
}

#endif
