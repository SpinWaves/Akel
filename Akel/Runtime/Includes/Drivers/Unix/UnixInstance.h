// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_DRIVERS_UNIX_INSTANCE_H
#define AK_DRIVERS_UNIX_INSTANCE_H

#include <Drivers/Unix/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace Ak
{
	class AK_UNIX_API UnixInstance final : public OSInstance
	{
		public:
			UnixInstance() = default;

			void Init(int ac, char** av);
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL([[maybe_unused]] const std::string& url) override;
			void Delay(std::uint32_t us) override;

			~UnixInstance() override = default;

		private:
			char** m_av = nullptr;
			int m_ac;
	};
}

#endif
