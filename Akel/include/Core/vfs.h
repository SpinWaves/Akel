// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 06/06/2023

#ifndef __AK_VIRTUAL_FILE_SYSTEM__
#define __AK_VIRTUAL_FILE_SYSTEM__

#include <Akpch.h>
#include <Core/log.h>

namespace Ak
{
	class AK_API VFS
	{
		public:
			VFS() = delete;

			static std::filesystem::path resolve(std::filesystem::path file);
			inline static const std::filesystem::path& mainDirPath() const { return _main_path; }
			inline static const std::filesystem::path& logDirPath() const { return Core::log::getLogDirPath(); }
			
			~VFS() = delete;

		private:
			friend int main(int argc, char** argv);
			inline static void init(const char* path)
			{
				_main_path = path;
				_main_path.remove_filename();

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
			inline static std::filesystem::path _main_path;
	};
}

#endif
