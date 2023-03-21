// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/03/2023
// Updated : 21/03/2023

#ifndef __AK_LUA_SCRIPT__
#define __AK_LUA_SCRIPT__

#include <Akpch.h>
#include <Modules/Scripting/script.h>

namespace Ak
{
	class AK_API LuaScript : public Script
	{
		friend class LuaLoader;

		public:
			LuaScript() = default;

			void runOnInit() override;
			void runOnUpdate(float delta) override;
			void runOnQuit() override;

			~LuaScript() = default;

		private:
			sol::protected_function _on_init;
			sol::protected_function _on_update;
			sol::protected_function _on_quit;
	};
}

#endif
