// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/02/2024
// Updated : 13/02/2024

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
			LibFunc GetSymbol(const char* symbol) const override;

			[[nodiscard]]
			bool Load(const std::filesystem::path& path) override;
			void UnloadCurrentLib() override;

			~MacOSLibLoader() = default;

		private:
			void* m_handle = nullptr;
	};
}

#endif
