// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 18/02/2024

#ifndef __AK_DRIVERS_UNIX_INSTANCE__
#define __AK_DRIVERS_UNIX_INSTANCE__

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
