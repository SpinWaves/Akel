// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 03/02/2024

#ifndef __AK_CORE_OS__
#define __AK_CORE_OS__

#include <Core/PreCompiled.h>

namespace Ak
{
	class OSInstance
	{
		public:
			OSInstance() = default;

			virtual void Init() = 0;
			virtual void Shutdown() = 0;

			virtual std::filesystem::path GetExecutablePath() = 0;
			virtual std::filesystem::path GetCurrentWorkingDirectoryPath() = 0;
			virtual bool OpenURL([[maybe_unused]] const std::string& url) { return false; }
			virtual void Delay(std::uint32_t ms) {}

			virtual ~OSInstance() = default;

		private:
	};
}

#endif
