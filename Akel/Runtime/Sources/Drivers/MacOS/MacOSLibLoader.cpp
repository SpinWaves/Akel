// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 04/05/2024

#include <Drivers/MacOS/MacOSLibLoader.h>
#include <Core/Logs.h>

namespace Ak
{
	[[nodiscard]]
	LibFunc MacOSLibLoader::GetSymbol(LibModule module, const char* symbol) const
	{
		void* ptr = dlsym(module, symbol);
		if(ptr == nullptr)
		{
			Error("MacOS Library loader : could not load '%' symbol", symbol);
			return nullptr;
		}
		LibFunc func;
		*(void**)(&func) = ptr;
		return func;
	}

	[[nodiscard]]
	LibModule MacOSLibLoader::Load(const std::filesystem::path& path)
	{
		LibModule module;
		if(!std::filesystem::exists(path))
		{
			Error("MacOS Library loader : invalid library file; %", path);
			return NullModule;
		}

		module = dlopen(path.string().data(), RTLD_LAZY | RTLD_GLOBAL);
		if(module == NullModule)
		{
			Error("MacOS Library loader : could not load %", path);
			return NullModule;
		}
		return module;
	}

	void MacOSLibLoader::UnloadLib(LibModule module)
	{
		if(module != NullModule)
			dlclose(module);
	}
}
