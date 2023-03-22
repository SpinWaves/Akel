// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/03/2023
// Updated : 22/03/2023

#ifndef __AK_NATIVE_SCRIPT_LOADER__
#define __AK_NATIVE_SCRIPT_LOADER__

#include <Akpch.h>
#include <Modules/Scripting/script_loader.h>
#include <Modules/Scripting/Native/native_script.h>

namespace Ak
{
	class AK_API NativeLoader : public ScriptLoader
	{
		public:
			NativeLoader() = default;

			Script* loadScript(std::filesystem::path script_file) override; 
			Script* loadScript(std::function<void(void)> init, std::function<void(float)> update, std::function<void(void)> quit);

			~NativeLoader() = default;
	};
}

#endif
