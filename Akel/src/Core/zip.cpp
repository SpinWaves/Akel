// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/07/2023
// Updated : 10/07/2023

#include <Core/zip.h>
#include <Core/log.h>

namespace Ak
{
	Zip::Zip(const std::filesystem::path& path)
	{
		if(std::filesystem::exists(path))
			_zip = zip_open(path.string().c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
		else
			_zip = zip_open(path.string().c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	}

	std::string Zip::getFileFromZip(const std::string& filename)
	{
		if(zip_entry_open(_zip, filename.c_str()))
			return {};
		std::string data;
		data.reserve(zip_entry_size(_zip));
		if(zip_entry_noallocread(_zip, data.data(), data.capacity()))
			return {};
		zip_entry_close(_zip);
		return data;
	}

	bool Zip::writeFileToZip(const std::filesystem::path& path, const std::string& filename)
	{
		std::ifstream is(path);
		if(!is.is_open())
		{
			Core::log::report(ERROR, "Archive : unable to open '%s'", path.string().c_str());
			return false;
		}
		std::stringstream buffer;
		buffer << is.rdbuf();
		return writeFileDataToZip(filename, buffer.str());
	}

	bool Zip::writeFileDataToZip(const std::string& path, const std::string& filedata)
	{
		if(zip_entry_open(_zip, path.c_str()) != 0)
			return false;
		if(zip_entry_write(_zip, filedata.data(), filedata.length()))
			return false;
		zip_entry_close(_zip);
		return true;
	}

	Zip::~Zip()
	{
		zip_close(_zip);
	}
}
