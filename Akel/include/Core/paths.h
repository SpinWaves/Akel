// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 04/06/2023

#ifndef __AK_PATHS__
#define __AK_PATHS__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak::Core
{
    class AK_API Paths
    {
		public:
			Paths() = delete;
			inline static void init(const char* path)
			{
				_main_path = path;
				_main_path.remove_filename();
			}
			inline static std::filesystem::path mainDirPath() { return _main_path; }
			static std::filesystem::path logDirPath();
			~Paths() = delete;

		private:
			inline static std::filesystem::path _main_path;
    };
    inline std::filesystem::path getMainDirPath() { return Paths::mainDirPath(); }
	inline std::filesystem::path getLogsDirPath() { return Paths::logDirPath(); }
}

#endif // __AK_PATHS__
