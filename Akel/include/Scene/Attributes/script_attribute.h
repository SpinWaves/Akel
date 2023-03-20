// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 20/03/2023

#ifndef __AK_SCRIPT_ATTRIBUTE__
#define __AK_SCRIPT_ATTRIBUTE__

#include <Akpch.h>
#include <Modules/Scripting/script.h>

namespace Ak
{
	class AK_API ScriptAttribute
	{
		friend class Scene;

		public:
			ScriptAttribute() = default;
			ScriptAttribute(const Script& script) : _script(script) {}
			ScriptAttribute(Script&& script) : _script(std::move(script)) {}
			~ScriptAttribute() = default;

		private:
			inline void onInit() { _script.runOnInit(); }
			inline void onUpdate(float delta) { _script.runOnUpdate(delta); }
			inline void onQuit() { _script.runOnQuit(); }
			
			Script _script;
	};
}

#endif
