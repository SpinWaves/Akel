// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 04/05/2024

#include <Drivers/Unix/UnixLibLoader.h>
#include <Core/Logs.h>

namespace Ak
{
	[[nodiscard]]
	LibFunc UnixLibLoader::GetSymbol(LibModule module, const char* symbol) const
	{
		void* ptr = dlsym(module, symbol);
		if(ptr == nullptr)
		{
			Error("Unix Library loader : could not load '%' symbol", symbol);
			return nullptr;
		}
		LibFunc func;
		*(void**)(&func) = ptr;
		return func;
	}

	[[nodiscard]]
	LibModule UnixLibLoader::Load(const std::filesystem::path& path)
	{
		LibModule module;
		if(!std::filesystem::exists(path))
		{
			Error("Unix Library loader : invalid library file; %", path);
			return NullModule;
		}

		dlerror(); // clears error flag
		module = dlopen(path.string().data(), RTLD_LAZY | RTLD_GLOBAL);
		if(module == NullModule)
		{
			Error("Unix Library loader : could not load %; %", path, dlerror());
			return NullModule;
		}
		return module;
	}

	void UnixLibLoader::UnloadLib(LibModule module)
	{
		if(module != NullModule)
			dlclose(module);
	}
}
