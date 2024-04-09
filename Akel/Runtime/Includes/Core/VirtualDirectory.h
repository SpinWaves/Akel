// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2024
// Updated : 09/04/2024

#ifndef __AK_CORE_VIRTUAL_DIRECTORY__
#define __AK_CORE_VIRTUAL_DIRECTORY__

#include <Core/PreCompiled.h>
#include <Utils/NonCopyable.h>
#include <Core/VirtualPath.h>
#include <Core/File.h>

namespace Ak
{
	struct FileEntry
	{
		SharedPtr<File> file;
	};

	struct DirectoryEntry
	{
		SharedPtr<class VirtualDirectory> virtual_directory;
	};

	struct Entry
	{
		std::string name;
		std::variant<FileEntry, DirectoryEntry> entry;
	};

	class AK_CORE_API VirtualDirectory : public NonCopyable, EnableSharedFromThis<VirtualDirectory>
	{
		public:
			VirtualDirectory(const WeakPtr<VirtualDirectory>& parent, const std::string& name);

			void MountRealDirectory(const std::filesystem::path& path);

			template <typename F>
			inline void ForEachEntries(F&& f);

			FileEntry GetFileEntry(std::string_view path);
			DirectoryEntry GetDirectoryEntry(std::string_view path);

			~VirtualDirectory();

		private:
			void ReleaseFromParent() noexcept;

		private:
			std::string m_name;
			std::vector<std::filesystem::path> m_mounted_directories;
			std::vector<Entry> m_entries;
			WeakPtr<VirtualDirectory> m_parent;
	};
}

#include <Core/VirtualDirectory.inl>

#endif
