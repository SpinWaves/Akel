// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 05/02/2023

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
			inline static std::string mainDirPath() { return _main_path.string(); }
			inline static std::string logDirPath();
			~Paths() = delete;

		private:
			inline static std::filesystem::path _main_path;
    };
    inline std::string getMainDirPath() { return Paths::mainDirPath(); }
	inline std::string getLogsDirPath() { return Paths::logDirPath(); }
}

#endif // __AK_PATHS__
