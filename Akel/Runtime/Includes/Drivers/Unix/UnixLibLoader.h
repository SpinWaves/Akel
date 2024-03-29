// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 13/02/2024

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
			LibFunc GetSymbol(const char* symbol) const override;

			[[nodiscard]]
			bool Load(const std::filesystem::path& path) override;
			void UnloadCurrentLib() override;

			~UnixLibLoader() = default;

		private:
			void* m_handle = nullptr;
	};
}

#endif
