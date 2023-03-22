// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/03/2023
// Updated : 22/03/2023

#include <Core/core.h>
#include <Modules/Scripting/Native/native_loader.h>

namespace Ak
{
	Script* NativeLoader::loadScript(std::filesystem::path script_file)
	{
		Core::log::report(ERROR, "Native Loader : native loader is not ment to load files, only c++ functions");
		return nullptr;
	}

	Script* NativeLoader::loadScript(std::function<void(void)> init, std::function<void(float)> update, std::function<void(void)> quit)
	{
		NativeScript* script = memAlloc<NativeScript>();
		script->_on_init = std::move(init);
		script->_on_update = std::move(update);
		script->_on_quit = std::move(quit);
		return script;
	}
}
