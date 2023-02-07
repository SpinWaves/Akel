// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 27/01/2023

#ifndef __AK_PROJECT_FILE__
#define __AK_PROJECT_FILE__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	namespace Core
	{
		using json = nlohmann::json;

		class AK_API ProjectFile
		{
			public:
				ProjectFile() = default;

				void initProjFile();

				void setDir(const std::string& dir);
				void setName(const std::string& name);

				bool getBoolValue(const std::string& key);
				int getIntValue(const std::string& key);
				float getFloatValue(const std::string& key);
				std::string getStringValue(const std::string& key);

				void setStringValue(const std::string& key, const std::string& value);
				void setIntValue(const std::string& key, const int value);
				void setBoolValue(const std::string& key, const bool value);
				void setFloatValue(const std::string& key, const float value);

				inline bool keyExists(const std::string& key) { return _json.contains(key); }

				~ProjectFile() = default;

			private:
				void write_file();

				json _json;
				std::vector<uint8_t> _data;
				std::string _name = "application";
				std::string _dir;
		};
	}
	Core::ProjectFile& getMainAppProjectFile();
}

#endif // __AK_PROJECT_FILE__
