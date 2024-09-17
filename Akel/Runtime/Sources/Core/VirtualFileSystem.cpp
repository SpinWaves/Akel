// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
