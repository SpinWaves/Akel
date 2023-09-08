// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 09/09/2023

#include <Core/vfs.h>
#include <Core/log.h>

namespace Ak
{
	namespace Core::log::internal
	{
		const std::filesystem::path& getLogPath();
	}

	const std::filesystem::path& VFS::getLogDirPath() { return Core::log::internal::getLogPath(); }

	std::filesystem::path VFS::resolve(const std::string& file)
	{
		if(file.compare(0, 2, ":/") == 0)
			return _main_path / file.substr(2, std::string::npos);
		if(file.compare(0, 2, "//") == 0)
		{
			std::size_t slash = file.find_first_of("/", 2);
			std::string_view virtualDir = std::string_view(file);
			virtualDir = virtualDir.substr(2, slash - 2);

			auto it = _mounts.find(virtualDir);
			if(it == _mounts.end() || it->second.empty())
				return "";

			std::string remainder = file.substr(virtualDir.size() + 3, file.size() - virtualDir.size());
			for(const std::filesystem::path& physicalPath : it->second)
			{
				std::filesystem::path newPath = physicalPath / remainder;
				if(std::filesystem::exists(newPath))
					return newPath;
			}
			Core::log::report(ERROR, "Virtual File System : cannot resolve physical path for '%s'", file.c_str());
		}
		return file;
	}

	void VFS::mountFolder(const std::string& virtual_path, const std::filesystem::path& physical_path, bool replace)
	{
		if(replace)
			_mounts[virtual_path].clear();
		_mounts[virtual_path].push_back(physical_path);
	}

	void VFS::unmountFolder(const std::string& virtual_path)
	{
		_mounts[virtual_path].clear();
	}

	void VFS::initResSystem()
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
}
