// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/05/2023
// Updated : 05/06/2023

#include <Core/file_loader.h>
#include <Core/log.h>

using json = nlohmann::json;

namespace Ak
{
	bool loadJson(std::filesystem::path file, json& j)
	{
		if(!std::filesystem::exists(file))
			return false;
		std::ifstream f(std::move(file), std::ios::binary);
		if(!f.is_open())
			return false;
		try
		{
			j = json::parse(f);
		}
		catch(json::parse_error& e)
		{
			f.unsetf(std::ios::skipws);

			f.seekg(0, std::ios::end);
			std::size_t fileSize = f.tellg();
			f.seekg(0, std::ios::beg);

			std::vector<uint8_t> data;
			data.reserve(fileSize);
			data.insert(data.begin(), std::istream_iterator<uint8_t>(f), std::istream_iterator<uint8_t>());
			j = json::from_msgpack(std::move(data));
		}
		f.close();
		return true;
	}

	void writeJson(const json& data, std::filesystem::path file, bool raw_json)
	{
		std::filesystem::remove(file);
		std::ofstream newFile(std::move(file), std::ios::ate | std::ios::binary);
		if(!newFile.is_open())
		{
			Core::log::report(ERROR, "File loader: unable to write data file: unable to create new file : '%s'", file.string().c_str());
			return;
		}
#ifdef AK_RELEASE
		if(!raw_json)
		{
			std::vector<uint8_t> vec;
			vec = json::to_msgpack(data);
			for(uint8_t byte : vec)
				newFile << byte;
		}
		else
			newFile << std::setw(4) << data << std::endl;
#else
		newFile << std::setw(4) << data << std::endl;
#endif
		newFile.close();
	}
}
