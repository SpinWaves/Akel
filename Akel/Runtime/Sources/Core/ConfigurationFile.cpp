// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/03/2024
// Updated : 19/03/2024

#include <Core/ConfigurationFile.h>
#include <Core/File.h>
#include <Core/Logs.h>

namespace Ak
{
	ConfigurationFile::ConfigurationFile(const std::filesystem::path& filepath)
	{
		try
		{
			m_table = toml::parse_file(filepath.string());
		}
		catch(const toml::parse_error& err)
		{
			Error("Configuration File : error while parsing '%', %", filepath, err);
		}
	}

	void ConfigurationFile::WriteToFile() const
	{
		File file(m_filepath, FileModeOverride);
		file << m_table;
	}
}
