// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/06/2023
// Updated : 06/06/2023

#include <Core/vfs.h>
#include <Core/paths.h>

namespace Ak
{
	std::filesystem::path VFS::resolve(std::filesystem::path file)
	{
		std::string resolver = file.string();
		if(resolver.compare(0, 2, ":/") == 0)
			return Core::getMainDirPath() / resolver.substr(2, std::string::npos);
		return file;
	}
}
