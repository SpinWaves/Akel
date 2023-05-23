// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 23/05/2023

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
		void ProjectFile::initProjFile(bool force_raw_json)
		{
			_force_raw_json = force_raw_json;
			std::filesystem::path f(__FILEPATH);
			if(!std::filesystem::exists(f))
			{
				_json = json::parse(R"({})");
				writeFile();
				_first_time_running = true;
			}
			else
			{
				if(!loadJson(__FILEPATH, _json))
					Core::log::report(FATAL_ERROR, "Unable to load project file");
				_first_time_running = false;
			}
		}

		void ProjectFile::writeFile()
		{
			writeJson(_json, __FILEPATH, _force_raw_json);
		}
	}
}

#undef __FILEPATH
