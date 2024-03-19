// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/03/2024
// Updated : 18/03/2024

#include <Core/File.h>
#include <Core/Logs.h>

namespace Ak
{
	File::File(const std::filesystem::path& filepath, std::uint32_t flags)
	{
		Open(filepath, flags);
	}

	bool File::Open(const std::filesystem::path& filepath, std::uint32_t flags)
	{
		if(!m_filepath.empty())
		{
			Error("File : cannot open a new file because this File handler has already another file opened");
			return false;
		}
		m_filepath = filepath;
		std::ios_base::openmode mode;
		mode = (flags & FileModeAppend ? mode | std::ios::app : mode);
		mode = (flags & FileModeBinary ? mode | std::ios::binary : mode);
		mode = (flags & FileModeOverride ? mode | std::ios::trunc : mode);
		m_stream.open(filepath, mode);
		return m_stream.is_open();
	}

	void File::Close()
	{
		m_stream.close();
		m_filepath.clear();
	}
}
