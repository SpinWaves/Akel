// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/03/2023
// Updated : 25/03/2023

#ifndef __AK_NATIVE_SCRIPT__
#define __AK_NATIVE_SCRIPT__

#include <Akpch.h>
#include <Modules/Scripting/script.h>

namespace Ak
{
	class AK_API NativeScript : public Script
	{
		friend class NativeLoader;

		public:
			NativeScript() = default;

			inline void runOnInit(Entity* this_entity) override { if(_on_init) _on_init(); }
			inline void runOnUpdate(Entity* this_entity, float delta) override { if(_on_update) _on_update(delta); }
			inline void runOnQuit(Entity* this_entity) override { if(_on_quit) _on_quit(); }

			~NativeScript() = default;

		private:
			std::function<void(void)> _on_init;
			std::function<void(float)> _on_update;
			std::function<void(void)> _on_quit;
	};
}

#endif
