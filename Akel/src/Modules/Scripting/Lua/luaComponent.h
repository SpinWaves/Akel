// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 18/01/2023

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

			void attach_script(std::filesystem::path path);

			~LuaComponent() = default;

		private:
			void bindLogs();
			void bindInputs(Input& in);

			sol::state _state;
			sol::load_result _script;
			sol::protected_function_result _guard;
	};
}

#endif
