// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2023
// Updated : 20/03/2023

#ifndef __AK_SCRIPT_LOADER__
#define __AK_SCRIPT_LOADER__

#include <Akpch.h>
#include <Modules/Scripting/script.h>

namespace Ak
{
	class AK_API ScriptLoader
	{
		public:
			virtual ScriptLoader() = default;

			virtual Script loadScript(std::filesystem::path script_file) = 0;

			virtual ~ScriptLoader() = default;

		protected:
			void setupScript(Script& script, std::function<void(void)> init, std::function<void(void)> update, std::function<void(void)> quit);
	};
}

#endif
