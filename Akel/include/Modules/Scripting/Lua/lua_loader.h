// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 22/03/2023

#ifndef __AK_LUA_LOADER__
#define __AK_LUA_LOADER__

#include <Akpch.h>
#include <Modules/Scripting/script_loader.h>

namespace Ak
{
	class AK_API LuaLoader : public ScriptLoader
	{
		public:
			LuaLoader(const class Input& input);

			Script* loadScript(std::filesystem::path lua_file) override;

			~LuaLoader() = default;

		private:
			void bindLogs();
			void bindInputs(const class Input& in);
			void bindECS();
	};
}

#endif
