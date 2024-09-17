// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/VirtualDirectory.h>

namespace Ak
{
	VirtualDirectory::VirtualDirectory(const WeakPtr<VirtualDirectory>& parent, const std::string& name) : m_name(name), m_parent(parent)
	{
	}

	void VirtualDirectory::MountRealDirectory(const std::filesystem::path& path)
	{
		if(!std::filesystem::exists(path))
		{
			Error("Cannot mount '%' to virtual directory '%' as this path doesn't exists", path, m_name);
			return;
		}
		if(!std::filesystem::is_directory(path))
		{
			Error("Cannot mount '%' to virtual directory '%' as this path is not a directory", path, m_name);
			return;
		}
		if(std::find(m_mounted_directories.begin(), m_mounted_directories.end(), path) != m_mounted_directories.end())
		{
			Warning("'%' directory is already mounted into %", path, m_name);
			return;
		}
		m_mounted_directories.push_back(path);

		for(auto const& entry : std::filesystem::directory_iterator{ path })
		{
			if(entry.is_directory())
				m_entries.emplace_back(entry.path().filename(), DirectoryEntry{ MakeShared<VirtualDirectory>(WeakFromThis(), entry.path().filename()) });
			else if(entry.is_character_file() || entry.is_regular_file() || entry.is_other())
				m_entries.emplace_back(entry.path().filename(), FileEntry{ MakeShared<File>(entry.path()) });
		}
	}

	FileEntry VirtualDirectory::GetFileEntry(std::string_view path)
	{
		auto it = std::find_if(m_entries.begin(), m_entries.end(), [=](const Entry& entry)
		{
			return entry.name == path;
		});
		if(it != m_entries.end() && std::holds_alternative<FileEntry>(it->entry))
			return std::get<FileEntry>(it->entry);
		return FileEntry{ nullptr };
	}

	DirectoryEntry VirtualDirectory::GetDirectoryEntry(std::string_view path)
	{
		auto it = std::find_if(m_entries.begin(), m_entries.end(), [=](const Entry& entry)
		{
			return entry.name == path;
		});
		if(it != m_entries.end() && std::holds_alternative<DirectoryEntry>(it->entry))
			return std::get<DirectoryEntry>(it->entry);
		return DirectoryEntry{ nullptr };
	}

	void VirtualDirectory::ReleaseFromParent() noexcept
	{
		m_parent.Reset();
	}

	VirtualDirectory::~VirtualDirectory()
	{
	}
}
