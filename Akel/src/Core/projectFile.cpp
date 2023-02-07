// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 15/11/2022

#include <Core/core.h>

#define __FILEPATH _dir + _name + std::string(".akel")

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
			if(_dir.back() != '/')
				_dir.push_back('/');
			std::filesystem::path f(__FILEPATH);
			if(!std::filesystem::exists(f))
				write_file();
			else
			{
				std::ifstream file(__FILEPATH, std::ios::binary);
				if(!file.is_open())
				{
					Core::log::report(ERROR, "config file manager: unable to open " + __FILEPATH);
					return;
				}

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

		void ProjectFile::setDir(const std::string& dir)
		{
			_dir = dir;
		}

		void ProjectFile::setName(const std::string& name)
		{
			_name = name;
		}

		bool ProjectFile::getBoolValue(const std::string& key)
		{
			if(!_json.contains(key))
				return false;
			return _json[key];
		}
		
		int ProjectFile::getIntValue(const std::string& key)
		{
			if(!_json.contains(key))
				return -1;
			return _json[key];
		}
		
		float ProjectFile::getFloatValue(const std::string& key)
		{
			if(!_json.contains(key))
				return -1.0f;
			return _json[key];
		}

		std::string ProjectFile::getStringValue(const std::string& key)
		{
			if(!_json.contains(key))
				return "";
			return _json[key];
		}

		void ProjectFile::setStringValue(const std::string& key, const std::string& value)
		{
			_json[key] = value;
			write_file();
		}

		void ProjectFile::setIntValue(const std::string& key, const int value)
		{
			_json[key] = value;
			write_file();
		}

		void ProjectFile::setBoolValue(const std::string& key, const bool value)
		{
			_json[key] = value;
			write_file();
		}

		void ProjectFile::setFloatValue(const std::string& key, const float value)
		{
			_json[key] = value;
			write_file();
		}

		void ProjectFile::write_file()
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
