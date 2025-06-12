// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_DRIVERS_WINDOWS_INSTANCE_H
#define AK_DRIVERS_WINDOWS_INSTANCE_H

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
