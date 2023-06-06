// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 07/06/2023

#include <Core/vfs.h>
#include <Core/log.h>

namespace Ak
{
	const std::filesystem::path& VFS::getLogDirPath() { return Core::log::getLogPath(); }

	std::filesystem::path VFS::resolve(const std::string& file)
	{
		if(file.compare(0, 2, ":/") == 0)
			return _main_path / file.substr(2, std::string::npos);
		return file;
	}
}
