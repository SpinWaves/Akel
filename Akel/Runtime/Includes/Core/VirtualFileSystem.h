// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/03/2024
// Updated : 19/03/2024

#ifndef __AK_CORE_VIRTUAL_FILE_SYSTEM__
#define __AK_CORE_VIRTUAL_FILE_SYSTEM__

#include <Core/PreCompiled.h>
#include <Core/Singleton.h>
#include <Core/File.h>

namespace Ak
{
	class AK_CORE_API FileSystem : Singleton<FileSystem>
	{
		friend Singleton<FileSystem>;

		public:

		private:
			FileSystem() = default;
			~FileSystem() = default;
	};
}

#endif
