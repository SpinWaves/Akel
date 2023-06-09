// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 09/06/2023

#include <Core/vfs.h>
#include <Core/log.h>

namespace Ak
{
	const std::filesystem::path& VFS::getLogDirPath() { return Core::log::getLogPath(); }

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

			const std::string remainder = file.substr(virtualDir.size() + 2, file.size() - virtualDir.size());
			for(const std::filesystem::path& physicalPath : it->second)
			{
				const std::string newPath = physicalPath + remainder;
				if(std::filesystem::exists(std::filesystem::path{ newPath }))
					return newPath;
			}
		}
		return file;
	}

	void VFS::mountFolder(const std::string& virtual_path, const std::filesystem::path& physical_path, bool replace)
	{
		if(replace)
			_mounts[virutal_path].clear();
		_mounts[virtual_path].push_back(physical_path);
	}

	void VFS::unmountFolder(const std::string& virtual_path)
	{
		_mounts[virutal_path].clear();
	}
}
