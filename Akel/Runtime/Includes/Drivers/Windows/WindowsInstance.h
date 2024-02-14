// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 13/02/2024

#ifndef __AK_DRIVERS_WINDOWS_INSTANCE__
#define __AK_DRIVERS_WINDOWS_INSTANCE__

#include <Drivers/Windows/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace Ak
{
	class AK_WINDOWS_API WindowsInstance final : public OSInstance
	{
		public:
			WindowsInstance() = default;

			void Init() override;
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL(const std::string& url) override;
			void Delay(std::uint32_t us) override;

			bool SetTitleBarColor(Vec4f color, bool dark = true) override;

			~WindowsInstance() = default;
	};
}

#endif
