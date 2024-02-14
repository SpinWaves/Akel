// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 13/02/2024

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
	LibFunc WindowsLibLoader::GetSymbol(const char* symbol) const
	{
		LibFunc func = reinterpret_cast<LibFunc>(::GetProcAddress(m_handle, symbol));
		if(func == nullptr)
		{
			Error("Windows Library loader : could not load '%' symbol", symbol);
			return nullptr;
		}
		return func;
	}

	[[nodiscard]]
	bool WindowsLibLoader::Load(const std::filesystem::path& path)
	{
		if(!std::filesystem::exists(path))
		{
			Error("Windows Library loader : invalid library file; %", path);
			return false;
		}

		if(m_handle != nullptr)
		{
			Warning("Windows Library loader : overriding '%' by '%'", GetCurrentlyLoadedLib(), path);
			UnloadCurrentLib();
		}

		m_handle = ::LoadLibraryA(path.string().data());
		if(m_handle == nullptr)
		{
			Error("Windows Library loader : could not load '%'", path);
			return false;
		}
		return true;
	}

	void WindowsLibLoader::UnloadCurrentLib()
	{
		if(m_handle != nullptr)
		{
			::FreeLibrary(m_handle);
			m_handle = nullptr;
		}
	}
}
