// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/01/2023
// Updated : 21/01/2023

#ifndef __AK_STUDIO_PROJECT_MANAGER_
#define __AK_STUDIO_PROJECT_MANAGER_

#include <AkSpch.h>

using json = nlohmann::json;

class ProjectManager
{
	public:
		ProjectManager() = default;

		bool openProjectFile(const std::filesystem::path& path);

		bool getBoolValue(const std::string& key);
		int getIntValue(const std::string& key);
		float getFloatValue(const std::string& key);
		std::string getStringValue(const std::string& key);

		void setStringValue(const std::string& key, const std::string& value);
		void setIntValue(const std::string& key, const int value);
		void setBoolValue(const std::string& key, const bool value);
		void setFloatValue(const std::string& key, const float value);

		inline bool keyExists(const std::string& key) { return _json.contains(key); }

		~ProjectManager() = default;

	private:
		void write_file();

		json _json;
		std::vector<uint8_t> _data;
		std::filesystem::path _path;
};

#endif
