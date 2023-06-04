// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 04/06/2023

#ifndef __AK_VIRTUAL_FILE_SYSTEM__
#define __AK_VIRTUAL_FILE_SYSTEM__

#include <Akpch.h>

namespace Ak
{
	class AK_API VFS
	{
		public:
			VFS() = delete;
			static std::filesystem::path resolve(std::filesystem::path file);
			~VFS() = delete;
	};
}

#endif
