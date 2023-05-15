// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 15/05/2023

#include <Core/core.h>

#define __FILEPATH _dir / (_name + std::string(".akel"))

namespace Ak
{
	Core::ProjectFile* __main_app_project_file = nullptr;

	Core::ProjectFile& getMainAppProjectFile()
	{
		return *__main_app_project_file;
	}

	namespace Core
	{
		void ProjectFile::initProjFile()
		{
			std::filesystem::path f(__FILEPATH);
			if(!std::filesystem::exists(f))
				writeFile();
			else
			{
				std::ifstream file(__FILEPATH, std::ios::binary);
				if(!file.is_open())
					Core::log::report(FATAL_ERROR, std::string("config file manager: unable to open " + f.string()));

				file.unsetf(std::ios::skipws);

				file.seekg(0, std::ios::end);
				std::size_t fileSize = file.tellg();
				file.seekg(0, std::ios::beg);
				
				_data.reserve(fileSize);
				_data.insert(_data.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());

				file.close();

				_json = json::from_msgpack(_data);
			}
		}

		void ProjectFile::writeFile()
		{
			std::filesystem::remove(__FILEPATH);
			std::ofstream newFile(__FILEPATH, std::ios::ate | std::ios::binary);
			if(!newFile.is_open())
			{
				Core::log::report(FATAL_ERROR, "Project file manager: unable to modify project file: unable to create new file");
				return;
			}
			_data = json::to_msgpack(_json);
			for(uint8_t byte : _data)
				newFile << byte;
			newFile.close();
		}
	}
}

#undef __FILEPATH
