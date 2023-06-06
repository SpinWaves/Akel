// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 07/06/2023

#ifndef __AK_VIRTUAL_FILE_SYSTEM__
#define __AK_VIRTUAL_FILE_SYSTEM__

#include <Akpch.h>
#include <Core/core.h>

int main(int, char**);

namespace Ak
{
	class AK_API VFS
	{
		friend int ::main(int, char**);
		friend bool initAkel(AkelInstance* project);
		public:
			VFS() = delete;

			static std::filesystem::path resolve(const std::string& file);
			inline static const std::filesystem::path& getMainDirPath() { return _main_path; }
			static const std::filesystem::path& getLogDirPath();

			~VFS() = delete;

		private:
			inline static void init(const char* path)
			{
				_main_path = path;
				_main_path.remove_filename();
			}
			inline static void initResSystem()
			{
				if(getMainAppProjectFile().archive()["use_default_resource_system"])
				{
					std::filesystem::create_directory(_main_path / "Resources");
					std::filesystem::create_directory(_main_path / "Resources/Textures");
					std::filesystem::create_directory(_main_path / "Resources/Meshes");
					std::filesystem::create_directory(_main_path / "Resources/Scripts");
					std::filesystem::create_directory(_main_path / "Resources/Scenes");
					std::filesystem::create_directory(_main_path / "Resources/Sounds");
				}
			}

		private:
			//inline static std::vector<>
			inline static std::filesystem::path _main_path;
	};
}

#endif
