// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 04/05/2024

#ifndef __AK_UNIX_LIB_LOADER__
#define __AK_UNIX_LIB_LOADER__

#include <Drivers/Unix/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace Ak
{
	class AK_UNIX_API UnixLibLoader : public LibLoader
	{
		public:
			UnixLibLoader() = default;

			[[nodiscard]]
			LibFunc GetSymbol(LibModule module, const char* symbol) const override;

			[[nodiscard]]
			LibModule Load(const std::filesystem::path& path) override;
			void UnloadLib(LibModule module) override;

			~UnixLibLoader() = default;
	};
}

#endif
