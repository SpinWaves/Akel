// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2023
// Updated : 20/03/2023

#include <Modules/Scripting/script_loader.h>

namespace Ak
{
	void ScriptLoader::setupScript(Script& script, std::function<void(void)> init, std::function<void(void)> update, std::function<void(void)> quit)
	{
		script._on_init = std::move(init);
		script._on_update = std::move(update);
		script._on_quit = std::move(quit);
	}
}
