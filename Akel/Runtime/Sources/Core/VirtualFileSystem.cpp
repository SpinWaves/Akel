// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/04/2024
// Updated : 04/05/2024

#include <Core/VirtualFileSystem.h>

namespace Ak
{
	VirtualFileSystem::VirtualFileSystem() : m_root({}, "/")
	{
		DebugLog("Virtual Filesystem is up");
	}

	bool VirtualFileSystem::CreateVirtualDirectory(std::string_view path, std::string_view directory_name)
	{
	}

	bool VirtualFileSystem::MountVirtualDirectory(const std::filesystem::path& real_directory, const VirtualPath& virtual_directory)
	{
	}
}
