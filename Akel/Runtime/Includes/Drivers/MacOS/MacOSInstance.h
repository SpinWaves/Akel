// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_DRIVERS_MACOS_INSTANCE__
#define __AK_DRIVERS_MACOS_INSTANCE__

#include <Drivers/MacOS/PreCompiled.h>
#include <Core/OS/OSInstance.h>

namespace Ak
{
	class AK_MACOS_API MacOSInstance final : public OSInstance
	{
		public:
			MacOSInstance() = default;

			void Init(int ac, char** av);
			void Shutdown() override;

			[[nodiscard]]
			std::filesystem::path GetExecutablePath() override;
			[[nodiscard]]
			std::filesystem::path GetCurrentWorkingDirectoryPath() override;
			bool OpenURL([[maybe_unused]] const std::string& url) override;
			void Delay(std::uint32_t us) override;

			bool SetTitleBarColor(Vec4f color, bool dark = true) override;

			~MacOSInstance() override = default;
	};
}

#endif
