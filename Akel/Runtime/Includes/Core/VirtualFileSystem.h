// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_CORE_VIRTUAL_FILE_SYSTEM__
#define __AK_CORE_VIRTUAL_FILE_SYSTEM__

#include <Core/PreCompiled.h>
#include <Core/File.h>
#include <Core/VirtualPath.h>
#include <Core/VirtualDirectory.h>

namespace Ak
{
	class AK_CORE_API VirtualFileSystem
	{
		friend class CoreModule;

		public:
			bool CreateVirtualDirectory(std::string_view path, std::string_view directory_name);
			bool MountVirtualDirectory(const std::filesystem::path& real_directory, const VirtualPath& virtual_directory);

		private:
			VirtualFileSystem();
			~VirtualFileSystem() = default;

		private:
			VirtualDirectory m_root;
	};
}

#endif
