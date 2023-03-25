// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/03/2023
// Updated : 25/03/2023

#ifndef __AK_LUA_SCRIPT__
#define __AK_LUA_SCRIPT__

#include <Akpch.h>
#include <Modules/Scripting/script.h>
#include <Scene/entity.h>

namespace Ak
{
	class AK_API LuaScript : public Script
	{
		friend class LuaLoader;

		public:
			LuaScript();

			void runOnInit(Entity* this_entity) override;
			void runOnUpdate(Entity* this_entity, float delta) override;
			void runOnQuit(Entity* this_entity) override;

			~LuaScript() = default;

		private:
			sol::protected_function _on_init;
			sol::protected_function _on_update;
			sol::protected_function _on_quit;
			int32_t _id = -1;
	};
}

#endif
