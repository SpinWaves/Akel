// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
