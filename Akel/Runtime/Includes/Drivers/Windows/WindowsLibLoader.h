// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_WINDOWS_LIB_LOADER_H
#define AK_WINDOWS_LIB_LOADER_H

#include <Drivers/Windows/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace Ak
{
	class AK_WINDOWS_API WindowsLibLoader : public LibLoader
	{
		public:
			WindowsLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~WindowsLibLoader() = default;
	};
}

#endif
