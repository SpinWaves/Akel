// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 15/05/2023

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

				inline void setDir(const std::filesystem::path& dir) { _dir = dir; }
				inline void setName(const std::string& name) { _name = name; }
				inline bool keyExists(const std::string& key) { return _json.contains(key); }

				inline json& operator()() { return _json; }
				inline json& archive() { return _json; }

				void writeFile();

				~ProjectFile() = default;

			private:
				json _json;
				std::vector<uint8_t> _data;
				std::filesystem::path _dir;
				std::string _name = "application";
		};
	}
	Core::ProjectFile& getMainAppProjectFile();
}

#endif // __AK_PROJECT_FILE__
