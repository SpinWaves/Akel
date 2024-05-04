// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 04/05/2024

#include <Drivers/Windows/WindowsLibLoader.h>
#include <Core/Logs.h>

#if defined(_MINWINDEF_)
	/* minwindef.h defines FARPROC, and attempting to redefine it may conflict with -Wstrict-prototypes */
#elif defined(_WIN64)
	typedef __int64 (__stdcall* FARPROC)(void);
#else
	typedef int (__stdcall* FARPROC)(void);
#endif
__declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) int __stdcall FreeLibrary(HMODULE);

namespace Ak
{
	[[nodiscard]]
	LibFunc WindowsLibLoader::GetSymbol(LibModule module, const char* symbol) const
	{
		LibFunc func = reinterpret_cast<LibFunc>(::GetProcAddress(module, symbol));
		if(func == nullptr)
		{
			Error("Windows Library loader : could not load '%' symbol", symbol);
			return nullptr;
		}
		return func;
	}

	[[nodiscard]]
	LibModule WindowsLibLoader::Load(const std::filesystem::path& path)
	{
		LibModule module;
		if(!std::filesystem::exists(path))
		{
			Error("Windows Library loader : invalid library file; %", path);
			return NullModule;
		}

		module = ::LoadLibraryA(path.string().data());
		if(module == NullModule)
		{
			Error("Windows Library loader : could not load '%'", path);
			return NullModule;
		}
		return module;
	}

	void WindowsLibLoader::UnloadLib(LibModule module)
	{
		if(module != NullModule)
			::FreeLibrary(module);
	}
}
