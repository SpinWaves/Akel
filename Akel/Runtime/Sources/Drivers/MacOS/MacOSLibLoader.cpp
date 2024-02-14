// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 13/02/2024

#include <Drivers/MacOS/MacOSLibLoader.h>
#include <Core/Logs.h>

namespace Ak
{
	[[nodiscard]]
	LibFunc MacOSLibLoader::GetSymbol(const char* symbol) const
	{
		void* ptr = dlsym(m_handle, symbol);
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
	bool MacOSLibLoader::Load(const std::filesystem::path& path)
	{
		if(!std::filesystem::exists(path))
		{
			Error("MacOS Library loader : invalid library file; %", path);
			return false;
		}

		if(m_handle != nullptr)
		{
			Warning("MacOS Library loader : overriding '%' by '%'", GetCurrentlyLoadedLib(), path);
			UnloadCurrentLib();
		}

		m_handle = dlopen(path.string().data(), RTLD_LAZY | RTLD_GLOBAL);
		if(m_handle == nullptr)
		{
			Error("MacOS Library loader : could not load '%'", path);
			return false;
		}
		return true;
	}

	void MacOSLibLoader::UnloadCurrentLib()
	{
		if(m_handle != nullptr)
		{
			dlclose(m_handle);
			m_handle = nullptr;
		}
	}
}
