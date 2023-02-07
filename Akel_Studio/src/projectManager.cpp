// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/01/2023
// Updated : 22/01/2023

#include <projectManager.h>

bool ProjectManager::openProjectFile(const std::filesystem::path& path)
{
	_path = path;
	if(!std::filesystem::exists(_path))
		write_file();
	else
	{
		std::ifstream file(_path, std::ios::binary);
		if(!file.is_open())
		{
			Ak::Core::log::report(ERROR, "project file manager: unable to open " + _path.string());
			return false;
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
	return true;
}

std::optional<bool> ProjectManager::getBoolValue(const std::string& key)
{
	if(!_json.contains(key))
		return std::nullopt;
	return _json[key];
}

std::optional<int> ProjectManager::getIntValue(const std::string& key)
{
	if(!_json.contains(key))
		return std::nullopt;
	return _json[key];
}

std::optional<float> ProjectManager::getFloatValue(const std::string& key)
{
	if(!_json.contains(key))
		return std::nullopt;
	return _json[key];
}

std::optional<std::string> ProjectManager::getStringValue(const std::string& key)
{
	if(!_json.contains(key))
		return std::nullopt;
	return _json[key];
}

void ProjectManager::setStringValue(const std::string& key, const std::string& value)
{
	_json[key] = value;
	write_file();
}

void ProjectManager::setIntValue(const std::string& key, const int value)
{
	_json[key] = value;
	write_file();
}

void ProjectManager::setBoolValue(const std::string& key, const bool value)
{
	_json[key] = value;
	write_file();
}

void ProjectManager::setFloatValue(const std::string& key, const float value)
{
	_json[key] = value;
	write_file();
}

void ProjectManager::write_file()
{
	std::filesystem::remove(_path);
	std::ofstream newFile(_path, std::ios::ate | std::ios::binary);
	if(!newFile.is_open())
	{
		Ak::Core::log::report(FATAL_ERROR, "Project file manager: unable to modify project file: unable to create new file");
		return;
	}
	_data = json::to_msgpack(_json);
	for(uint8_t byte : _data)
		newFile << byte;
	newFile.close();
}
