// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 25/03/2023

#ifndef __AK_SCRIPT_ATTRIBUTE__
#define __AK_SCRIPT_ATTRIBUTE__

#include <Akpch.h>
#include <Modules/Scripting/script.h>

namespace Ak
{
	class ScriptAttribute
	{
		friend class Scene;

		public:
			ScriptAttribute() = default;
			ScriptAttribute(Script* script) : _script(script) {}
			~ScriptAttribute() = default;

		private:
			inline void onInit(Entity* entity) { if(_script != nullptr) _script->runOnInit(entity); }
			inline void onUpdate(Entity* entity, float delta) { if(_script != nullptr) _script->runOnUpdate(entity, delta); }
			inline void onQuit(Entity* entity) { if(_script != nullptr) _script->runOnQuit(entity); }
			
			Script* _script = nullptr;
	};
}

#endif
