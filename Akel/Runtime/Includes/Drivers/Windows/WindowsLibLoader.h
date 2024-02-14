// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/02/2024
// Updated : 13/02/2024

#ifndef __AK_WINDOWS_LIB_LOADER__
#define __AK_WINDOWS_LIB_LOADER__

#include <Drivers/Windows/PreCompiled.h>
#include <Core/OS/LibLoader.h>

typedef const char* LPCSTR;
typedef struct HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;

namespace Ak
{
	class AK_WINDOWS_API WindowsLibLoader : public LibLoader
	{
		public:
			WindowsLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(const char* symbol) const override;

			[[nodiscard]]
			bool Load(const std::filesystem::path& path) override;
			void UnloadCurrentLib() override;

			~WindowsLibLoader() = default;

		private:
			HMODULE m_handle;
	};
}

#endif
