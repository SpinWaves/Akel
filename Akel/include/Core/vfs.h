// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 09/06/2023

#ifndef __AK_VIRTUAL_FILE_SYSTEM__
#define __AK_VIRTUAL_FILE_SYSTEM__

#include <Akpch.h>
#include <Core/core.h>

int main(int, char**);

namespace Ak
{
	enum class VirtualFolder
	{
		Meshes
		Scenes,
		Scripts,
		Sounds,
		Textures,
	};

	class AK_API VFS
	{
		friend int ::main(int, char**);
		friend bool initAkel(AkelInstance* project);
		public:
			VFS() = delete;

			static std::filesystem::path resolve(const std::string& file);
			inline static const std::filesystem::path& getMainDirPath() { return _main_path; }
			static const std::filesystem::path& getLogDirPath();
			static void mountFolder(const std::string& virtual_path, const std::filesystem::path& physical_path, bool replace = false);
			static void unmountFolder(const std::string& virtual_path);

			template <VirtualFolder folder>
			inline static void mountFolderAs(const std::filesystem::path& physical_path, bool replace = false)
			{
				switch(folder)
				{
					case VirtualFolder::Meshes : mountFolder("Meshes", physical_path, replace); return;
					case VirtualFolder::Scenes : mountFolder("Scenes", physical_path, replace); return;
					case VirtualFolder::Scripts : mountFolder("Scripts", physical_path, replace); return;
					case VirtualFolder::Sounds : mountFolder("Sounds", physical_path, replace); return;
					case VirtualFolder::Textures : mountFolder("Textures", physical_path, replace); return;
				}
			}

			~VFS() = delete;

		private:
			struct Directory

		private:
			inline static void init(const char* path)
			{
				_main_path = path;
				_main_path.remove_filename();
			}
			inline static void initResSystem()
			{
				if(!getMainAppProjectFile().archive()["use_default_resource_system"])
					return;
				std::filesystem::create_directory(_main_path / "Resources");
				std::filesystem::create_directory(_main_path / "Resources/Textures");
				std::filesystem::create_directory(_main_path / "Resources/Meshes");
				std::filesystem::create_directory(_main_path / "Resources/Scripts");
				std::filesystem::create_directory(_main_path / "Resources/Scenes");
				std::filesystem::create_directory(_main_path / "Resources/Sounds");
				mountFolderAs<VirtualFolder::Textures>(_main_path / "Resources/Textures", true);
				mountFolderAs<VirtualFolder::Scenes>(_main_path / "Resources/Scenes", true);
				mountFolderAs<VirtualFolder::Scripts>(_main_path / "Resources/Scripts", true);
				mountFolderAs<VirtualFolder::Meshes>(_main_path / "Resources/Meshes", true);
				mountFolderAs<VirtualFolder::Sounds>(_main_path / "Resources/Sounds", true);
			}

		private:
			inline static std::map<std::string, std::vector<std::filesystem::path>, std::less<void>> _mounts;
			inline static std::filesystem::path _main_path;
	};
}

#endif
