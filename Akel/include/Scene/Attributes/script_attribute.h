// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 21/03/2023

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
			ScriptAttribute(Script* script) : _script(script) { onInit(); }
			~ScriptAttribute() = default;

		private:
			inline void onInit() { if(_script != nullptr) _script->runOnInit(); }
			inline void onUpdate(float delta) { if(_script != nullptr) _script->runOnUpdate(delta); }
			inline void onQuit() { if(_script != nullptr) _script->runOnQuit(); }
			
			Script* _script = nullptr;
	};
}

#endif
