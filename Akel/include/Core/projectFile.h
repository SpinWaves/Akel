// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 18/05/2023

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

				void initProjFile(bool force_raw_json);

				inline void setDir(const std::filesystem::path& dir) { _dir = dir; }
				inline void setName(const std::string& name) { _name = name; }
				inline const std::filesystem::path& getDir() const noexcept { return _dir; }
				inline const std::string& getName() const noexcept { return _name; }
				inline bool keyExists(const std::string& key) { return _json.contains(key); }
				inline bool isFirstTimeRunning() const noexcept { return _first_time_running; }

				inline json& operator()() { return _json; }
				inline json& archive() { return _json; }

				void writeFile();

				~ProjectFile() = default;

			private:
				json _json;
				std::vector<uint8_t> _data;
				std::filesystem::path _dir;
				std::string _name = "application";
				bool _force_raw_json;
				bool _first_time_running = true;
		};
	}
	Core::ProjectFile& getMainAppProjectFile();
}

#endif // __AK_PROJECT_FILE__
