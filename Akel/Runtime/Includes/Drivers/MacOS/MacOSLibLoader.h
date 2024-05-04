// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/02/2024
// Updated : 04/05/2024

#ifndef __AK_MACOS_LIB_LOADER__
#define __AK_MACOS_LIB_LOADER__

#include <Drivers/MacOS/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace Ak
{
	class AK_MACOS_API MacOSLibLoader : public LibLoader
	{
		public:
			MacOSLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~MacOSLibLoader() = default;

		private:
			void* m_handle = nullptr;
	};
}

#endif
